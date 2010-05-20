#ifndef _FALLING_INCLUDES_H_
#define _FALLING_INCLUDES_H_

//Bibliotecas-padrão
#include <string>
#include <cstdlib>
#include <math.h>

//Bibliotecas extras
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

namespace line_collapser
{

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

BLOCK_COLOR game_matrix[MATRIX_HEIGHT][MATRIX_WIDTH] //[linha][coluna]
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

//Game Area Attributes
const int BLOCK_SIZE = 20;
	//caixa do jogo
const int GAME_X = 267;
const int GAME_Y = 40;
const int GAME_WIDTH = MATRIX_WIDTH * BLOCK_SIZE;
const int GAME_HEIGHT = MATRIX_HEIGHT * BLOCK_SIZE;
	//caixa do next
const int NEXT_X = 76;
const int NEXT_Y = 200;
const int NEXT_WIDTH = 100;
const int NEXT_HEIGHT = 100;
	//caixa do score
const int SCORE_X = 46;
const int SCORE_Y = 40;
const int SCORE_WIDTH = 160;
const int SCORE_HEIGHT = 70;
	//caixa da line
const int LINE_X = 520;
const int LINE_Y = 153;
const int LINE_WIDTH = 70;
const int LINE_HEIGHT = 50;
	//caixa do level
const int LEVEL_X = 520;
const int LEVEL_Y = 223;
const int LEVEL_WIDTH = 70;
const int LEVEL_HEIGHT = 50;


//Velocidade do bloco (em movimentos por segundo)
int block_mps = 1;

//Dados
int score = 0;
int level = 1;
int line = 0;

//Screen
SDL_Surface* screen = NULL;

//Images
SDL_Surface* background = NULL;

//Fonts
TTF_Font* font = NULL;

//Texts
SDL_Surface* Sscore = NULL;
SDL_Surface* Sline = NULL;
SDL_Surface* Slevel = NULL;

//Sprites
SDL_Surface* block_colors [COLORS_AMOUNT];

//Event
SDL_Event eventQ;






/************************************************/
//Functions

///**************************************///
///****************Basic*****************///
///**************************************///

//Inicializa o sistema
int init();

//Carrega os arquivos necessários
bool load_files();

//Libera a memória e encerra o sistema
void end_app();



/************************************************/
/****************Basic Drawing*******************/
/************************************************/

SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);


/************************************************/
/**************Especific Drawing*****************/
/************************************************/

//Insere um bloco de acordo com a matriz
void insert_block (int x, int y, BLOCK_COLOR color = NONE);

//Insere um bloco na caixa next (com x,y relativo ao interior da caixa)
void insert_next (int x, int y, BLOCK_COLOR color);

//Desenha a pontuação
void print_score (int scoreNum);

//Desenha a quantidade de linhas
void print_line (int lineNum);

//Desenha o nível
void print_level (int levelNum);

//Desenha a matriz
void paint_matrix ();

/************************************************/
/******************Event Handle******************/
/************************************************/

//Retira uma linha da matriz
void collapse_line (int line);

//Checa por linhas completas e retorna um vetor no formato:
//{ qtd de linhas, linha 1, linha 2, linha 3, linha 4 }
int* check_lines();

//Gera um tetramino aleatório
//(poderia usar direto a função 'random()', mas aqui posso usar um seed diferente sem comprometer o código)
int get_next();


}//namespace

#endif
