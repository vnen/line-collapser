#ifndef _FALLING_INCLUDES_H_
#define _FALLING_INCLUDES_H_


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

namespace line_collapser
{

//Screen Attributes
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480
#define SCREEN_BPP  32

//Frames per second
#define GAME_FPS  60

//Colors
#define COLORS_AMOUNT  7
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
#define MATRIX_WIDTH  10
#define MATRIX_HEIGHT  20

extern BLOCK_COLOR game_matrix[MATRIX_HEIGHT][MATRIX_WIDTH];

//Game Area Attributes
#define BLOCK_SIZE  20
	//caixa do jogo
#define GAME_X  267
#define GAME_Y  40
#define GAME_WIDTH  MATRIX_WIDTH * BLOCK_SIZE
#define GAME_HEIGHT  MATRIX_HEIGHT * BLOCK_SIZE
	//caixa do next
#define NEXT_X  76
#define NEXT_Y  200
#define NEXT_WIDTH  100
#define NEXT_HEIGHT  100
	//caixa do score
#define SCORE_X  46
#define SCORE_Y  40
#define SCORE_WIDTH  160
#define SCORE_HEIGHT  70
	//caixa da line
#define LINE_X  520
#define LINE_Y  153
#define LINE_WIDTH  70
#define LINE_HEIGHT  50
	//caixa do level
#define LEVEL_X  520
#define LEVEL_Y  223
#define LEVEL_WIDTH  70
#define LEVEL_HEIGHT  50


//Velocidade do bloco (em movimentos por segundo)
extern int block_mps;

//Dados
extern int score;
extern int level;
extern int line;

//Screen
extern SDL_Surface* screen;

//Images
extern SDL_Surface* background;

//Fonts
extern TTF_Font* font;

//Texts
extern SDL_Surface* Sscore;
extern SDL_Surface* Sline;
extern SDL_Surface* Slevel;

//Sprites
extern SDL_Surface* block_colors [COLORS_AMOUNT];

//Event
extern SDL_Event eventQ;






/************************************************/
//Functions

///**************************************///
///****************Basic*****************///
///**************************************///

//Inicializa o sistema
int init();

//Carrega os arquivos necessrios
bool load_files();

//Libera a memria e encerra o sistema
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

//Desenha a pontuao
void print_score (int scoreNum);

//Desenha a quantidade de linhas
void print_line (int lineNum);

//Desenha o nvel
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

//Gera um tetramino aleatrio
//(poderia usar direto a funo 'random()', mas aqui posso usar um seed diferente sem comprometer o cdigo)
int get_next();


}//namespace

#endif
