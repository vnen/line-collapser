#include "SDL.h"
#include "SDL_image.h"
#include "MyTimer.h"
#include <string>

//Screen Attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Frames per second
const int GAME_FPS = 60;

//Colors
const int COLORS_AMOUNT = 7;
enum BLOCK_COLOR 
{
	BLACK	,
	BLUE	,
	GREEN	,
	NAVY	,
	RED		,
	VIOLET	,
	YELLOW	,
	NONE = 99
};

//Matrix for game area
const int MATRIX_WIDTH = 10;
const int MATRIX_HEIGHT = 20;

BLOCK_COLOR game_matrix[MATRIX_WIDTH][MATRIX_HEIGHT]; //[linha][coluna]

//Game Area Attributes
const int BLOCK_SIZE = 20;

const int GAME_X = 267;
const int GAME_Y = 40;
const int GAME_WIDTH = MATRIX_WIDTH * BLOCK_SIZE;
const int GAME_HEIGHT = MATRIX_HEIGHT * BLOCK_SIZE;

const int NEXT_X = 76;
const int NEXT_Y = 200;
const int NEXT_WIDTH = 100;
const int NEXT_HEIGHT = 100;


//Screen
SDL_Surface* screen = NULL;

//Images
SDL_Surface* background = NULL;

//Sprites
SDL_Surface* block_colors [COLORS_AMOUNT];

//Event
SDL_Event event;

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
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

	return optimizedImage;
    
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Falling Hell", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the sprite sheet
    background = load_image( "images/background.png" );

	for (int i = 0; i < COLORS_AMOUNT; i++)
	{
		char tmp[21];
		sprintf_s(tmp, "images/block (%d).png", (i + 1));

		block_colors[i] = load_image( tmp );
	}

    //If there was a problem in loading the sprite
    if( background == NULL )
    {
        return false;
    }

	//Fill the game matrix with blank spaces
	for( int i = 0; i < MATRIX_WIDTH; i++)
		for( int j = 0; j < MATRIX_HEIGHT; j++)
		{
			game_matrix[i][j] = NONE;
		}

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface (background);
	
	for (int i = 0; i < COLORS_AMOUNT; i++)
	{
		SDL_FreeSurface (block_colors[i]);
	}

    //Quit SDL
    SDL_Quit();
}

//Insere um bloco de acordo com a matriz
void insert_block (int x, int y, BLOCK_COLOR color = NONE)
{
	if (color != NONE)
	{
		apply_surface ( (x * BLOCK_SIZE + GAME_X), (y * BLOCK_SIZE + GAME_Y), block_colors[(int)color], screen);
	}
}

//Insere um bloco na caixa next (com x,y relativo ao interior da caixa)
void insert_next (int x, int y, BLOCK_COLOR color = NONE)
{
	if (color != NONE)
	{
		apply_surface ( (x + NEXT_X), (y + NEXT_Y), block_colors[(int)color], screen);
	}
}

//Desenha a matriz
void paint_matrix ()
{
	//Percorre a matriz
	for( int i = 0; i < MATRIX_WIDTH; i++)
		for( int j = 0; j < MATRIX_HEIGHT; j++)
		{
			insert_block (i, j, game_matrix[i][j]);
		}
}


int main( int argc, char* args[])
{

	//Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 2;
    }
	
	/*insert_block (3,0,BLACK);
	insert_block (4,0,BLACK);
	insert_block (5,0,BLACK);
	insert_block (6,0,BLACK);
	*/

	using namespace falling_hell;

	//Frame rate timer
	Timer fps;

	//Frame atual
	int actual_frame = 0;

	//Linha atual
	int line = -1;

    //While the user hasn't quit
    while( quit == false )
    {
		//Initialize Timer
		fps.start();

		//Set the actual frame
		actual_frame++;

		//While there's events to handle
        while( SDL_PollEvent( &event ) )
        {

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
			if( event.type == SDL_KEYDOWN )
			{
				if( (event.key.keysym.sym == SDLK_F4) && (event.key.keysym.mod & KMOD_LALT) )
				{
					quit = true;
				}
			}
        }//while event

		//increase the line
		

		if ( ((actual_frame % GAME_FPS) == 0))
		{
			line++;
			if(line < MATRIX_HEIGHT)
			{

				game_matrix [3][line-1] = NONE;
				game_matrix [4][line-1] = NONE;
				game_matrix [5][line-1] = NONE;
				game_matrix [6][line-1] = NONE;

				game_matrix [3][line] = BLACK;
				game_matrix [4][line] = BLACK;
				game_matrix [5][line] = BLACK;
				game_matrix [6][line] = BLACK;
			}
		}

		apply_surface (0, 0, background, screen);

		insert_next ( ((NEXT_WIDTH - 2*BLOCK_SIZE)/2),((NEXT_HEIGHT - 2*BLOCK_SIZE)/2), BLUE );
		insert_next ( ((NEXT_WIDTH - 2*BLOCK_SIZE)/2) + BLOCK_SIZE,((NEXT_HEIGHT - 2*BLOCK_SIZE)/2), BLUE );
		insert_next ( ((NEXT_WIDTH - 2*BLOCK_SIZE)/2),((NEXT_HEIGHT - 2*BLOCK_SIZE)/2) + BLOCK_SIZE, BLUE );
		insert_next ( ((NEXT_WIDTH - 2*BLOCK_SIZE)/2) + BLOCK_SIZE,((NEXT_HEIGHT - 2*BLOCK_SIZE)/2) + BLOCK_SIZE, BLUE );

		paint_matrix();

		if( SDL_Flip( screen ) == -1 )
		{
			return 3;
		}

		//Cap the framerate
		if (fps.getTicks() < 1000 / GAME_FPS)
		{
			SDL_Delay ( (1000 / GAME_FPS) - fps.getTicks() );
		}
    }

    //Clean up
    clean_up();

    return 0;
}