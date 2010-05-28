#include "includes.h"
#include "mersenne_twister.h"
#include "lcwin32.h"
#include "Timer.h"

//Bibliotecas-padro
#include <string>
#include <cstdlib>
#include <math.h>

//Bibliotecas extras
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

//Dados
int score = 0;
int level = 1;
int line = 0;

//Screen
SDL_Surface* screen = NULL;

//Images
SDL_Surface* background = NULL;

//Sounds
Mix_Music* bgm = NULL;

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
	//Opens background image
	background = load_image ("images/background.png");
	if (background == NULL)
		{ return false; }

	//Opens background image
	bgm = Mix_LoadMUS ("sounds/mainbgm.ogg");
	if (bgm == NULL)
		{ return false; }

	font = TTF_OpenFont ("fonts/r-impresive_6.ttf", 16);

	for (int i = 0; i < LC_COLORS_AMOUNT; i++)
	{
		char tmp[21];
		sprintf(tmp, "images/block (%d).png", i+1);
		block_colors[i] = load_image (tmp);
		if (block_colors[i] == NULL)
			{ return false; }
	}

	return true;

}//load_files()


//Frees the memory and closes system
void end_app()
{
	//Stops the music
	Mix_HaltMusic();

	//Close the music
	Mix_FreeMusic(bgm);

	//Closes the font
	TTF_CloseFont (font);

	//Libera as surfaces
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
}


											/************************************************/
											/****************Basic Drawing*******************/
											/************************************************/

//Insere um bloco de acordo com a matriz
void insert_block (int x, int y, lcBlockColor color)
{
	if (color != NONE)
	{
		apply_surface ( (x * LC_BLOCK_SIZE + LC_GAME_X), (y * LC_BLOCK_SIZE + LC_GAME_Y), block_colors[(int)color], screen);
	}
}//insert_block

//Insere um bloco na caixa next (com x,y relativo ao interior da caixa)
void insert_next (int x, int y, lcBlockColor color)
{
	if (color != NONE)
	{
		apply_surface ( (x + LC_NEXT_X), (y + LC_NEXT_Y), block_colors[(int)color], screen);
	}
}//insert_next

//Desenha a pontuao
void print_score (int scoreNum)
{
	SDL_Color cor = {0,0,0};	//Cor RGB(0,0,0)
	char scoreChar[50];			//Score em 'char'

	sprintf(scoreChar, "%d", scoreNum);	//Converte o score para 'char'

	//Armazena a surface para o score
	SDL_FreeSurface (Sscore);
	Sscore = TTF_RenderText_Solid (font, scoreChar, cor);

	//Calcula a posio do score
	//(este deve ficar alinhado abaixo e a direita da caixa, com 5px de margem)
	int x = LC_SCORE_X + LC_SCORE_WIDTH - Sscore->w - 7;
	int y = LC_SCORE_Y + LC_SCORE_HEIGHT - Sscore->h - 5;

	//Aplica o texto
	apply_surface (x, y, Sscore, screen);
}//print_score


//Desenha a quantidade de linhas
void print_line (int lineNum)
{
	SDL_Color cor = {0,0,0};			//Cor RGB(0,0,0)
	char lineChar[50];					//Line em 'char'

	sprintf(lineChar, "%d", lineNum);	//Converte a line para 'char'

	//Armazena a surface para a line
	SDL_FreeSurface (Sline);
	Sline = TTF_RenderText_Solid (font, lineChar, cor);

	//Calcula a posio da line
	//(esta deve ficar centralizada na caixa, com 5px de margem para baixo)
	int x = LC_LINE_X + ((LC_LINE_WIDTH - Sline->w) / 2);
	int y = LC_LINE_Y + LC_LINE_HEIGHT - Sline->h - 5;

	//Aplica o texto
	apply_surface (x, y, Sline, screen);
}//print_line


//Desenha o nvel
void print_level (int levelNum)
{
	SDL_Color cor = {0,0,0};	//Cor RGB(0,0,0)
	char levelChar[50];			//Level em 'char'

	sprintf(levelChar, "%d", levelNum);	//Converte o level para 'char'

	//Armazena a surface para a level
	SDL_FreeSurface (Slevel);
	Slevel = TTF_RenderText_Solid (font, levelChar, cor);

	//Calcula a posio do level
	//(este deve ficar centralizado na caixa, com 5px de margem para baixo)
	int x = LC_LEVEL_X + ((LC_LEVEL_WIDTH - Slevel->w) / 2);
	int y = LC_LEVEL_Y + LC_LEVEL_HEIGHT - Slevel->h - 5;

	//Aplica o texto
	apply_surface (x, y, Slevel, screen);

}//print_level


//Desenha a matriz
void paint_matrix ()
{
	//Percorre a matriz
	for( int i = 0; i < LC_MATRIX_HEIGHT; i++)
		for( int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			insert_block (j, i, game_matrix[i][j]);
		}//for
}//paint_matrix

									/************************************************/
									/**************Especific Drawing*****************/
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

//Retira uma linha da matriz
void collapse_line (int line)
{
	//Percorre a partir da linha para cima
	for (int i = line; i >= 0; i--)
	{
		//Percorre cada clula dentro da linha
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			//Se for a linha mais alta (0) prenche com NONE, se no, apenas copia da linha de cima
			game_matrix[i][j] = (i == 0 ? NONE : game_matrix[i-1][j]);
		}//for
	}//for
}//void collapse_line (int line)





//Checa por linhas completas e retorna um vetor no formato:
//{ qtd de linhas, linha 1, linha 2, linha 3, linha 4 }
int* check_lines()
{
	//Armazena as informaes para retorno
	int* tmp;
	tmp = (int*) malloc( sizeof(int)*5 );
	for (int i = 0; i < 5; i++)
	{
		tmp[i] = 0;
	}//for

	//Armazena a quantidade de blocos por linha
	int filleds = 0;

	//Percorre cada uma das linhas
	for (int i = 0; i < LC_MATRIX_HEIGHT; i++)
	{
		//Percorre cada clula dentro da linha
		for (int j = 0; j < LC_MATRIX_WIDTH; j++)
		{
			//Se estiver preenchido
			if (game_matrix[i][j] != NONE)
			{
				//Acrescenta 1 aos filleds
				filleds++;
			}
		}//for (clulas)

		//Se todas esto preenchidas (filleds == 10)
		if (filleds == LC_MATRIX_WIDTH)
		{
			//Armazena no vetor de retorno, na posio seguinte
			//Isto depende da quantidade de linhas que j foram preenchidas
			switch (tmp[0])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				tmp[0] = tmp[0] + 1;
				tmp[tmp[0]] = i;
				break;

			//Se chegar no limite (4) j retorna para economizar CPU
			//e evitar um acesso indevido  memria
			case 4:
				tmp[0] = tmp[0] + 1;
				tmp[tmp[0]] = i;
				return tmp;

			}//switch

		}// if (filleds)
		filleds = 0;

	}//for (linhas)

	return tmp;
}//int* check_lines()





//Generates a random tetramino (a number between 0 and 6)
int get_next()
{
	//Returns a random number between 0 and 6
	//It uses
	return (int) mt_random() % 7 ;

}//int get_next()







//Pauses the game
/** returns 'true' if the user wants to quit */
bool lcpause()
{
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

	//Puts the matrix on screen
	paint_matrix();

	//Updates the screen and check against errors
	if (SDL_Flip(screen) == -1)
	{
		return true;
	}


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

	return quit;
}



}//namespace
