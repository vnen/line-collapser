#include "includes.h"
#include "mersenne_twister.h"
#include "lcwin32.h"
#include "Timer.h"
#include "sounds.h"

//Standard libraries
#include <string>
#include <cstdlib>
#include <math.h>

//SDL libraries
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

namespace line_collapser
{

											///**************************************///
											///**************Variables***************///
											///**************************************///

lcBlockColor game_matrix[LC_MATRIX_HEIGHT][LC_MATRIX_WIDTH] //[line][column]
=	{{NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
	 {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

//Blocks speeds (in moves per second) ****NOT USED
//int block_mps = 1;

//Data
int score = 0;
int level = 1;
int line = 0;

//Screen
SDL_Surface* screen = NULL;

//Images
SDL_Surface* background = NULL;
SDL_Surface* startscreen = NULL;

//Sounds
Mix_Music* sndBgm = NULL;

//Music and FX enabled state
bool music = false;
bool soundFX = false;

//Fonts
TTF_Font* font = NULL;

//Texts
SDL_Surface* Sscore = NULL;
SDL_Surface* Sline = NULL;
SDL_Surface* Slevel = NULL;

//Sprites
SDL_Surface* block_colors [LC_COLORS_AMOUNT];

//Event
SDL_Event eventQ;



										///**************************************///
										///****************Basic*****************///
										///**************************************///

//Initializes the system
int init()
{
	//Initializes the SDL and exit if there was an error
	if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
		{ return 1; }

	//Initializes the SDL_ttf and exit if there was an error
	if (TTF_Init())
		{ return 3; }

	//Initializes the SDL_mixer and exit if there was an error
	if (Mix_OpenAudio(LC_SOUND_SAMPLERATE, LC_SOUND_FORMAT, LC_SOUND_CHANNELS, LC_SOUND_CHUNKSIZE) == -1)
		{ return 4; }

	//Create the window
	screen = SDL_SetVideoMode (LC_SCREEN_WIDTH, LC_SCREEN_HEIGHT, LC_SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	//Load the necessary files and check for errors
	if (!load_files())
		{ return 5; }

	//Changes the window title
	SDL_WM_SetCaption ("Line Collapser", NULL);

	//If there was an error with the window creation, exits the program
	if (screen == NULL)
		{ return 6; }

	//Start the random number generation function
	mt_init();

	//If everything went fine
	return 0;

}//init()

//Loads the necessaries files
bool load_files()
{
	//Opens start screen image
	startscreen = load_image ("images/start.png");
	if (startscreen == NULL)
		{ return false; }

	//Opens background image
	background = load_image ("images/background.png");
	if (background == NULL)
		{ return false; }

	//Opens background music
	sndBgm = Mix_LoadMUS ("sounds/mainbgm.ogg");
	if (sndBgm == NULL)
		{ return false; } // I could remove this, sounds aren't essential for game
						  // But is a good thing for tests

	
	//Opens font (for score, line and level)
	font = TTF_OpenFont ("fonts/r-impresive_6.ttf", 16);

	for (int i = 0; i < LC_COLORS_AMOUNT; i++)
	{
		char tmp[21];
		sprintf(tmp, "images/block (%d).png", i+1);
		block_colors[i] = NULL;
		block_colors[i] = load_image (tmp);
		if (block_colors[i] == NULL)
			{ return false; }
	}

	return true;

}//load_files()


//Frees the memory and closes system
void end_app()
{
	end_app(0);
} //void end_app(int code)

//Frees memory and exit the system with a exit code
void end_app(int code)
{
	//Stops all sounds
	Mix_HaltMusic();
	Mix_HaltChannel(-1);

	//Close the music
	Mix_FreeMusic(sndBgm);

	//Closes the font
	TTF_CloseFont (font);

	//Frees the surfaces
	SDL_FreeSurface (background);
	for (int i = 0; i < LC_COLORS_AMOUNT; i++)
	{
		SDL_FreeSurface (block_colors[i]);
	}
	SDL_FreeSurface (Sscore);
	SDL_FreeSurface (Sline);

	//Closes the libraries
	Mix_CloseAudio();
	TTF_Quit ();
	SDL_Quit ();

	exit(code);
} //void end_app(int code)



											/************************************************/
											/****************Basic Drawing*******************/
											/************************************************/

//Insert a block, according to the matrix
void insert_block (int x, int y, lcBlockColor color)
{
	if (color != NONE)
	{
		apply_surface ( (x * LC_BLOCK_SIZE + LC_GAME_X), (y * LC_BLOCK_SIZE + LC_GAME_Y), block_colors[(int)color], screen);
	}
}//insert_block

//Insert a block in next box (with x,y relative to the interior of the box)
void insert_next (int x, int y, lcBlockColor color)
{
	if (color != NONE)
	{
		apply_surface ( (x + LC_NEXT_X), (y + LC_NEXT_Y), block_colors[(int)color], screen);
	}
}//insert_next

//Draws score
void print_score (int scoreNum)
{
	SDL_Color cor = {0,0,0};	//Color RGB(0,0,0)
	char scoreChar[50];			//Score in 'char'

	sprintf(scoreChar, "%d", scoreNum);	//Converts score to 'char'

	//Frees the old and store the new surface for score
	SDL_FreeSurface (Sscore);
	Sscore = TTF_RenderText_Solid (font, scoreChar, cor);

	//Calculate the score's position
	//(it must stay aligned down-right of the box, with a 5px margin)
	int x = LC_SCORE_X + LC_SCORE_WIDTH - Sscore->w - 7;
	int y = LC_SCORE_Y + LC_SCORE_HEIGHT - Sscore->h - 5;

	//Applies the text
	apply_surface (x, y, Sscore, screen);
}//print_score


//Draws the number of lines collapsed
void print_line (int lineNum)
{
	SDL_Color cor = {0,0,0};			//Color RGB(0,0,0)
	char lineChar[50];					//Line in 'char'

	sprintf(lineChar, "%d", lineNum);	//Converts line to 'char'

	//Frees the old and store the new surface for line
	SDL_FreeSurface (Sline);
	Sline = TTF_RenderText_Solid (font, lineChar, cor);

	//Calculate the line's position
	//(it must be centralized in the box, with a 5px margin-bottom)
	int x = LC_LINE_X + ((LC_LINE_WIDTH - Sline->w) / 2);
	int y = LC_LINE_Y + LC_LINE_HEIGHT - Sline->h - 5;

	//Applies the text
	apply_surface (x, y, Sline, screen);
}//print_line


//Draws the level
void print_level (int levelNum)
{
	SDL_Color cor = {0,0,0};	//Color RGB(0,0,0)
	char levelChar[50];			//Level in 'char'

	sprintf(levelChar, "%d", levelNum);	//Converts level to 'char'

	//Frees the old and store the new surface for score
	SDL_FreeSurface (Slevel);
	Slevel = TTF_RenderText_Solid (font, levelChar, cor);

	//Calculate level's position
	//(it must be centralized in the box, with a 5px margin-bottom)
	int x = LC_LEVEL_X + ((LC_LEVEL_WIDTH - Slevel->w) / 2);
	int y = LC_LEVEL_Y + LC_LEVEL_HEIGHT - Slevel->h - 5;

	//Applies the text
	apply_surface (x, y, Slevel, screen);

}//print_level


//Draws the matrix
void paint_matrix ()
{
	//Goes through matrix
	for( int i = 0; i < LC_MATRIX_HEIGHT; i++)
		for( int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			insert_block (j, i, game_matrix[i][j]);
		}//for
}//paint_matrix

									/************************************************/
									/***************Specific Drawing*****************/
									/************************************************/

SDL_Surface *load_image( std::string filename )
{
    //Image that's loaded
    SDL_Surface* loadedImage = NULL;

    //Optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
	{
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );
	}

	//Return the optimized surface
	return optimizedImage;
    
}//load_image

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}//apply_surface



										/************************************************/
										/*****************Game functions*****************/
										/************************************************/

//Collapse a line from matriz
void collapse_line (int line)
{
	//Goes through the matrix from the line to top
	for (int i = line; i >= 0; i--)
	{
		//Goes through each cell into the line
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			//If it is the line at the top (0) fills with NONE, else, just copy from the line above
			game_matrix[i][j] = (i == 0 ? NONE : game_matrix[i-1][j]);
		}//for
	}//for
}//void collapse_line (int line)





//Checks for full lines and returns a vector in the format:
//{ ammount of lines, line 1, line 2, line 3, line 4 }
int* check_lines()
{
	//Stores the information to return
	int* tmp;
	tmp = (int*) malloc( sizeof(int)*5 );
	for (int i = 0; i < 5; i++)
	{
		tmp[i] = 0;
	}//for

	//Stores the ammount of filled cells per line
	int filleds = 0;

	//Goes through each line
	for (int i = 0; i < LC_MATRIX_HEIGHT; i++)
	{
		//Goes through each cell inside the line
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			//If it is filled
			if (game_matrix[i][j] != NONE)
			{
				//Increments filleds
				filleds++;
			}
		}//for (cells)

		//If everyone is filled (filleds == width of matrix)
		if (filleds == LC_MATRIX_WIDTH)
		{
			//Stores in the return vector, in the next empty position
			//It depends on how many lines are filled and already checked
			switch (tmp[0])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				tmp[0] = tmp[0] + 1;
				tmp[tmp[0]] = i;
				break;

			//If it arrives the limit (4) returns at once to save CPU
			//and avoid a undue access to memory
			case 4:
				tmp[0] = tmp[0] + 1;
				tmp[tmp[0]] = i;
				return tmp;

			}//switch

		}// if (filleds)
		filleds = 0;

	}//for (lines)

	return tmp;
}//int* check_lines()




int tetraminos[6] = {0,0,0,0,0,2};
int actnext = 0;
//Generates a random tetramino (a number between 0 and 6)
int get_next()
{
	//Returns a random number between 0 and 6
	//It uses
	//return (int) mt_random() % 7 ;

	return tetraminos[(actnext++ % 6)];

}//int get_next()







//Pauses the game
/** returns 'true' if the user wants to quit */
bool lcpause()
{
	//No music when the game is paused
	int musicState = musicTogglePause();

	//Updates screen
	//Applies the background
	apply_surface(0, 0, background, screen);

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
		return true;
	}


	//Makes a backup of game_matrix
	lcBlockColor matrix_backup[LC_MATRIX_HEIGHT][LC_MATRIX_WIDTH];
	/** Make the screen full of grey blocks
	 * so the player won't have time to think when paused
	 * (cheating isn't allowed =P)
	 * Ah, and with a simple stacking animation
	 */
	for (int i = LC_MATRIX_HEIGHT - 1; i >= 0; i--)
	{
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			matrix_backup[i][j] = game_matrix[i][j];
			game_matrix[i][j] = GREY;
		}//for (each line)

		//So the animation
		//Puts the matrix on screen
		paint_matrix();

		//Updates the screen and check against errors
		if (SDL_Flip(screen) == -1)
		{
			return true;
		}
		SDL_Delay(20);

	}//for (each column)


	//If the user wants to quit while paused
	bool quit = false;

	//Create a loop like the main
	Timer fps;
	bool pause = true;
	while (pause)
	{
		//Starts the timer to cap the frame rate
		fps.start();

		//Captures the unpause and quit events
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
					pause = false;
					quit = true;								//Sets the flag to quit the main loop
				}
				if (eventQ.key.keysym.sym == SDLK_ESCAPE)		//If the user was pressed Esc
				{
					pause = false;
					quit = true;								//Sets the flag to quit the main loop
				}

				//If the user pressed the space bar
				if (eventQ.key.keysym.sym == SDLK_SPACE)
				{
					pause = false;
				}

				//If the user pressed the F1 key, shows help
				if (eventQ.key.keysym.sym == SDLK_F1)
				{

					showHelp();

					//The screen was changed, so we have to do this again:
					//Applies the background
					apply_surface(0, 0, background, screen);

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
					//Puts the matrix on screen
					paint_matrix();

					//Updates the screen and check against errors
					if (SDL_Flip(screen) == -1)
					{
						return true;
					}

				}

				//If the 'F' key was pressed, enable/disable sound FX
				if (eventQ.key.keysym.sym == SDLK_f)
				{
					soundFX = !soundFX;
				}

				//If the 'M' key was pressed, enable/disable music
				if (eventQ.key.keysym.sym == SDLK_m)
				{
					music = !music;
				}

				break;
			}//switch events
		}//while events

		/** Caps the frame rate
		 * We don't the game runs on a super speed (even if there is no animation)
		 * because it will consume CPU/RAM resources without needing
		 */
		if (fps.getTicks() < 1000 / LC_GAME_FPS)
			SDL_Delay ( (1000 / LC_GAME_FPS) - fps.getTicks());

	}//while (pause)

	//Turns back to the game
	for (int i = 0; i < LC_MATRIX_HEIGHT; i++)
	{
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			game_matrix[i][j] = matrix_backup[i][j];
		}//for (each line)
	}//for (each column)

	//Now we turn on the music again... if it is paused
	if (musicState == LC_MUSIC_PAUSED && music)
		musicTogglePause();

	return quit;
}








//Shows help screen
void showHelp()
{
	Timer fpscap;

	//Loads the image
	SDL_Surface* img = NULL;
	img = load_image("images/help.png");

	//Check if image was loaded fine
	if (img == NULL)
		end_app(70);

	//Applies image
	apply_surface(0, 0, img, screen);

	//Updates the screen and check against errors
	if (SDL_Flip(screen) == -1)
	{
		end_app(71);
	}

	bool quit = false;
	while (!quit)
	{
		fpscap.start();

		//Handle all the generated events
		while (SDL_PollEvent (&eventQ))
		{
			//Captures the type of event
			switch (eventQ.type)
			{
			//If the user try to close the window
			case SDL_QUIT:
				//Exit the game
				SDL_FreeSurface(img);
				end_app();
				break;
			//If the user has pressed a key
			case SDL_KEYDOWN:
				//All this stuff only to check the Alt+F4
				if(    (eventQ.key.keysym.sym == SDLK_F4)		//If the user was pressed F4
				   &&  (eventQ.key.keysym.mod & KMOD_LALT)		//and the left Alt key was pressed
				   && !(eventQ.key.keysym.mod & KMOD_CTRL)		//and the Ctrl key wasn't pressed
				   && !(eventQ.key.keysym.mod & KMOD_SHIFT))	//and the Shift key wasn't pressed
				{
					end_app();
				}
				if (eventQ.key.keysym.sym == SDLK_ESCAPE)		//If the user was pressed Esc
				{
					end_app();
				}
				//If user press 'F1', come back
				if (eventQ.key.keysym.sym == SDLK_F1)
				{
					quit = true;
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

				//If the 'F' key was pressed, enable/disable sound FX
				if (eventQ.key.keysym.sym == SDLK_f)
				{
					soundFX = !soundFX;
				}

			}//events switch
		}//events loop

		//Keep the frame rate
		if (fpscap.getTicks() < 1000 / LC_GAME_FPS)
			SDL_Delay ( (1000 / LC_GAME_FPS) - fpscap.getTicks());

	} //main loop

	SDL_FreeSurface(img);

}//void showHelp()


}//namespace
