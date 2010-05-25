#ifndef _LC_INCLUDES_H_
#define _LC_INCLUDES_H_


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

namespace line_collapser
{

//Screen Attributes
#define LC_SCREEN_WIDTH  640
#define LC_SCREEN_HEIGHT  480
#define LC_SCREEN_BPP  32

//Frames per second
#define LC_GAME_FPS  60

//Colors
#define LC_COLORS_AMOUNT  7
enum lcBlockColor 
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
#define LC_MATRIX_WIDTH  10
#define LC_MATRIX_HEIGHT  20

extern lcBlockColor game_matrix[LC_MATRIX_HEIGHT][LC_MATRIX_WIDTH];

//Game Area Attributes
#define LC_BLOCK_SIZE  20
	//game box
#define LC_GAME_X  267
#define LC_GAME_Y  40
#define LC_GAME_WIDTH  LC_MATRIX_WIDTH * LC_BLOCK_SIZE
#define LC_GAME_HEIGHT  LC_MATRIX_HEIGHT * LC_BLOCK_SIZE
	//next box
#define LC_NEXT_X  76
#define LC_NEXT_Y  200
#define LC_NEXT_WIDTH  100
#define LC_NEXT_HEIGHT  100
	//score box
#define LC_SCORE_X  46
#define LC_SCORE_Y  40
#define LC_SCORE_WIDTH  160
#define LC_SCORE_HEIGHT  70
	//line box
#define LC_LINE_X  520
#define LC_LINE_Y  153
#define LC_LINE_WIDTH  70
#define LC_LINE_HEIGHT  50
	//level box
#define LC_LEVEL_X  520
#define LC_LEVEL_Y  223
#define LC_LEVEL_WIDTH  70
#define LC_LEVEL_HEIGHT  50


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
extern SDL_Surface* block_colors [LC_COLORS_AMOUNT];

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
void insert_block (int x, int y, lcBlockColor color = NONE);

//Insere um bloco na caixa next (com x,y relativo ao interior da caixa)
void insert_next (int x, int y, lcBlockColor color);

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
