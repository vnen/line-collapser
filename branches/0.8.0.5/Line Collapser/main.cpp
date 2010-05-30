#include "Timer.h"
#include "Tetraminos.h"
#include "sounds.h"

#include <string>
#include <cstdlib>
#include <math.h>


int main (int argc, char* args[])
{
	int teste = 0;
	//Standard namespace
	using namespace line_collapser;
	
	//Initialization function
	//Exit the program if some error occurred
	int errorlevel = init();
	if(errorlevel >= 1)
	{ //If the SDL was initialized, turn it off
		SDL_Quit();

		if(errorlevel >= 3)
		{ //If the SDL_ttf was initialized, turn it off
			TTF_Quit();

			if(errorlevel >= 4)
			{ //If the SDL_mixer was initialized, turn it off
				Mix_CloseAudio();
			}// >=4
		}// >=3

		return errorlevel;

	}// init error


	//Timer to control the blocks speed (actually, it controls the frame rate)
	Timer fpscap;
	unsigned int frame = 0;

	//Tetraminos creation
	Tetramino* tetras[7];
	tetras[0] = new I();
	tetras[1] = new O();
	tetras[2] = new L();
	tetras[3] = new J();
	tetras[4] = new S();
	tetras[5] = new Z();
	tetras[6] = new T();
	
	/********************/
	//****** Data ******//
	/********************/

	//Music and FX enabled state
	bool music = false;
	bool soundFX = true;

	//If it is the first iteration
	bool first = true;
	
	//Actual Tetramino
	int actual = get_next();
	
	//Next Tetramino
	int next = get_next();
	
	//If it is collapsing lines
	bool collapsing = false;
	
	//Counting to make timing for animation
	int counting = 0;

	//Counting to wait the landing of Tetraminos
	Timer bottom;

	//A copy for some lines to make the collapsing animation
	lcBlockColor backup[4][LC_MATRIX_WIDTH];

	//A pointer to an integer array
	//The first element is the amount of lines
	//The others are the lines indexes
	int* fullLines = NULL;

	//Flags of players controlling
	bool moving_down = false;
	bool moving_left = false;
	bool moving_right = false;


	//Before start the main loop, start playing the background music
	bool playingBgm = false;
	if (music)
		playingBgm = line_collapser::playMainBgm();

	//To avoid warnings when it is still not used
	playingBgm = playingBgm;


	//Main loop
	bool quit = false;
	while (!quit)
	{
		fpscap.start();
		frame++;

		//Handle all the generated events
		while (SDL_PollEvent (&eventQ))
		{
			//Captures the type of event
			switch (eventQ.type)
			{
			//If the user try to close the window
			case SDL_QUIT:
				//Sets the flag to quit the main loop
				quit = true;
				break;
			//If the user has pressed a key
			case SDL_KEYDOWN:
				//All this stuff only to check the Alt+F4
				if(    (eventQ.key.keysym.sym == SDLK_F4)		//If the user was pressed F4
				   &&  (eventQ.key.keysym.mod & KMOD_LALT)		//and the left Alt key was pressed
				   && !(eventQ.key.keysym.mod & KMOD_CTRL)		//and the Ctrl key wasn't pressed
				   && !(eventQ.key.keysym.mod & KMOD_SHIFT))	//and the Shift key wasn't pressed
				{
					quit = true;								//Sets the flag to quit the main loop
				}
				if (eventQ.key.keysym.sym == SDLK_ESCAPE)		//If the user was pressed Esc
				{
					quit = true;								//Sets the flag to quit the main loop
				}

				//If the left arrow key was pressed, set the flag
				if(eventQ.key.keysym.sym == SDLK_LEFT)
				{
					moving_left = true;
				}
				//If the right arrow key was pressed, set the flag
				if(eventQ.key.keysym.sym == SDLK_RIGHT)
				{
					moving_right = true;
				}
				//If the down arrow key was pressed, set the flag
				if(eventQ.key.keysym.sym == SDLK_DOWN)
				{
					moving_down = true;
				}

				//If the 'Z' key was pressed, rotate (counter-clockwise)
				if (eventQ.key.keysym.sym == SDLK_z)
				{
					tetras[actual]->rotate();
				}

				//If the 'M' key was pressed, stops/plays music
				if (eventQ.key.keysym.sym == SDLK_m)
				{
					if(music)
					{
						Mix_HaltMusic();
						music = false;
					}
					else
					{
						int tmp = Mix_PlayMusic (sndBgm, -1);
						if(tmp != -1) music = true;
					}
				}

				//If the space bar was pressed, pause
				if (eventQ.key.keysym.sym == SDLK_SPACE)
				{
					/* If the player pauses the game,
					 * all the movements should be canceled
					 * because during pause we could miss a KEY_UP event
					 */
					moving_down = false;
					moving_left = false;
					moving_right = false;

					quit = lcpause();
				}
				break;

			//If the user is no longer pressing a key
			case SDL_KEYUP:
				//If the left arrow key was unpressed, unset the flag
				if(eventQ.key.keysym.sym == SDLK_LEFT)
				{
					moving_left = false;
				}
				//If the right arrow key was unpressed, unset the flag
				if(eventQ.key.keysym.sym == SDLK_RIGHT)
				{
					moving_right = false;
				}
				//If the down arrow key was unpressed, unset the flag
				if(eventQ.key.keysym.sym == SDLK_DOWN)
				{
					moving_down = false;
				}
			default:
				break;
			}//events switch
		}//events while



		//Movement controls and logics



		//If it is the first interaction
		/* NOTE:
		 * Maybe this could stand before the main loop
		 * but it'll remain this way for now
		 * I'll change when I put the start screen */
		if (first)
		{
			//Try to put the first Tetramino in the matrix
			//If it isn't possible, something is wrong so quit teh main loop
			if (!tetras[actual]->put_in_matrix(true))
				quit = true;
			//From now on, it won't be the first iteration
			first = false;

			//So we don't need to do nothing more, because we just put the first tetramino
			//All the logic will start in the next iteration
			//(hey it is just the single first frame)

		}//if (first)

		//If it isn't the first iteration, and it isn't collapsing lines
		else if (!collapsing)
		{
			//Every 0.1 second
			if (frame % (LC_GAME_FPS/10) == 0)
			{
				//If the user is pressing the left arrow, move to left
				if (moving_left)
					tetras[actual]->move_left();
				//If the user is pressing the right arrow, move to right
				if(moving_right)
					tetras[actual]->move_right();

			}// if (every 0.1 second)

			//Every 0.05 second and if the user is pressing the down arrow
			if ((moving_down && (frame % (LC_GAME_FPS/20)) == 0))
			{
				//Move down the Tetramino and check if it is possible
				bool scoring = tetras[actual]->move_down();
				
				//If it was possible to move, increase the score
				if (scoring) score++;
				//If it can't move anymore, cancel the next tries
				//else moving_down = false; //I think I don't need this

			}//if (every 0.05 second && moving_down)

			//Else, and if it is in time based on level
			else if ( (((frame % ((11 - level)*4)) == 0)))
			{
				//Try to move down, and if it can't
				if (!tetras[actual]->move_down())
				{
					//Start the timer, if it isn't already started
					if(!bottom.isStarted())
						bottom.start();
				} //if (can't move down)
				//If it moved down (this 'else' statement fix the 'flying tetraminos bug' partially)
				else
				{
					//Stops the timer
					bottom.stop();
				}
			}//if (it's time to move down)
			
			//If it tried to move down for time enough (750ms)
			if (bottom.isStarted() && bottom.getTicks() > 750)
			{
				//Try to move down once, if it's possible so the tetramino shouldn't land
				//It is the second and final part to fix the 'flying tetraminos bug'
				if (tetras[actual]->move_down())
				{
					bottom.stop();
				}// if(can move down yet)

				//If it isn't possible, so the tetramino must finally land
				else //it can't move down anymore
				{
					//Plays effect sooner as possible, because it seems that SDL_mixer have some delay on playing sounds
					playEffect(LC_SOUND_FX_LAND);

					//Stops the timer
					bottom.stop();

					//Resets the actual tetramino
					tetras[actual]->reset();

					//Checks for full lines
					fullLines = check_lines();

					//If there is full lines
					if (fullLines[0] > 0)
					{
						//Start the collapsing
						collapsing = true;

						//Check how many lines are full
						//and applies the correspondent score
						switch(fullLines[0])
						{
						case 1:
							score += 100;
							break;
						case 2:
							score += 200;
							break;
						case 3:
							score += 400;
							break;
						case 4:
							score += 800;
							break;
						default:
							break;
						}//switch (full lines)

						//Updates the line counter and the level
						line += fullLines[0];
						level = 1 + (int)floor((double)line / 10);
						//The level can be, at most, 10
						level = level < 10 ? level : 10;

					} //if (have full lines)
					//If there isn't
					else
						//Free the memory which will no longer be used
						free(fullLines);

					//If it is collapsing lines
					if (collapsing)
					{
						//Make a copy of the lines that are collapsing, just to make the animation
						//Goes through each column of the matrix
						for (int i = 0; i < LC_MATRIX_WIDTH; i++)
						{
							//For each line that needs to be removed
							for (int j = 0; j < fullLines[0]; j++)
							{
								//Copy to the backup, in the correspondent position
								backup[j][i] = game_matrix[fullLines[j+1]][i];

								// fullLines starts in 1, because fullLines[0] is the amount of lines

							}//for (fullLines)
						}//for (columns)

						//Plays the sound effect
						if(soundFX)
							playEffect(LC_SOUND_FX_COLLAPSE);

					}//if (collapsing)

					//If there's no needing to collapse lines
					else
					{
						//The next Tetramino now is the actual
						actual = next;
						//The next Tetramino is generated randomly
						next = get_next();

						//Try to put the next Tetramino on the matrix
						if (!tetras[actual]->put_in_matrix(true))
						{
							//If it isn't possible, game over
							//(here is the place to make an game over screen)
							quit = true;
						}//if (it couldn't put the next one on the matrix)

					}//if (there's no needing to collapse lines)

				}//if (it can't move down anymore)

			}//if (tried to move for time enough)

		}// if(!collapsing)

		//If it is collapsing lines
		if (collapsing)
		{
			{
				//Increment the animation counter
				counting++;

				//Animation
					/* The counting indicates in what step of the animation we are
					 * Every 6 (GAME_FPS/10) steps it alternates between show and hide the lines
					 * To show the lines we use the previous made backup
					 * In the last step the line is hidden
					 */

					if (counting <= (LC_GAME_FPS/10) || (counting > (2*LC_GAME_FPS/10) && counting <= (3*LC_GAME_FPS/10)) ||
							(counting > (4*LC_GAME_FPS/10) && counting <= (5*LC_GAME_FPS/10)) ||
							(counting > (6*LC_GAME_FPS/10) && counting <= (7*LC_GAME_FPS/10)) ||
							(counting > (8*LC_GAME_FPS/10) && counting <= (9*LC_GAME_FPS/10)))
					//Hides
					//This function is almost identical to the backuo function, but it erases instead copy
					for (int i = 0; i < LC_MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = NONE;
						}//for (each fullLine)
					}//for (each column)

					/* I think it's important to notice that the values in both if statements are the same
					 * What changes is the comparison operator
					 */
					if ((counting > (LC_GAME_FPS/10) && counting <= (2*LC_GAME_FPS/10)) ||
							(counting > (3*LC_GAME_FPS/10) && counting <= (4*LC_GAME_FPS/10)) ||
							(counting > (5*LC_GAME_FPS/10) && counting <= (6*LC_GAME_FPS/10)) ||
							(counting > (7*LC_GAME_FPS/10) && counting <= (8*LC_GAME_FPS/10)))
					//Shows
					//This function is almost identical to the backup function, but it copies from backup to matrix, instead the opposite
					for (int i = 0; i < LC_MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = backup[j][i];
						}//for (each fullLine)
					}//for (each column)


				//If the counting is beyond the last step
				if (counting > (9*LC_GAME_FPS/10))
				{
					//For each fullLine
					for (int i = 0; i < fullLines[0]; i++)
					{
						//Collapse the line
						collapse_line(fullLines[i+1]);
					}//for (each fullLine)

					//We're not collapsing lines anymore
					collapsing = false;

					//The next Tetramino now is the actual
					actual = next;

					//The next Tetramino is generated randomly
					next = get_next();

					//If it isn't possible, game over
					//(here is the place to make an game over screen)
					if (!tetras[actual]->put_in_matrix(true))
					{
						quit = true;
					}
					//Free the memory which will no longer be used
					free(fullLines);

					//Resets the animation steps counting
					counting = 0;
				}
			}
		}
							

		//Renderization
		//Applies the background
		apply_surface(0, 0, background, screen);

		//Draws the next tetramino
		tetras[next]->draw_in_next();

		//Writes the score
		print_score (score);

		//Writes the amount of lines collapsed
		print_line (line);

		//Writes the actual level
		print_level (level);

		//Puts the matrix on screen
		paint_matrix();

		//Updates the screen and check against errors
		if (SDL_Flip(screen) == -1)
		{
			quit = true;
		}

		//Keep the frame rate
		if (fpscap.getTicks() < 1000 / LC_GAME_FPS)
			SDL_Delay ( (1000 / LC_GAME_FPS) - fpscap.getTicks());

	}//while (main loop)

	//Finalization function
	end_app();

	return 0;
}
