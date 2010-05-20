#include "includes.h"

namespace line_collapser
{


										///**************************************///
										///****************Basic*****************///
										///**************************************///

//Inicializa o sistema
int init()
{
	//Inicializa o SDL e encerra se houver algum erro
	if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
		{ return 1; }

	//Inicializa o SDL_image e encerra se houver algum erro
	if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{ return 2; }

	//Inicializa a SDL_ttf e encerra se houver algum erro
	if (TTF_Init())
		{ return 3; }

	//Cria a janela
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	//Carrega os arquivos necess�rios e checa por erros
	if (!load_files())
		{ return 5; }

	//Alera o t�tulo 
	SDL_WM_SetCaption ("Line Collapser", NULL);

	//Se houve algum erro com a janela, encerrar
	if (screen == NULL)
		{ return 6; }

	//Se deu tudo certo
	return 0;

}//init()

//Carrega os arquivos necess�rios
bool load_files()
{
	background = load_image ("images/background.png");
	if (background == NULL)
		{ return false; }

	font = TTF_OpenFont ("fonts/r-impresive_6.ttf", 16);

	for (int i = 0; i < COLORS_AMOUNT; i++)
	{
		char tmp[21];
		sprintf_s(tmp, "images/block (%d).png", i+1);
		block_colors[i] = load_image (tmp);
		if (block_colors[i] == NULL)
			{ return false; }
	}

	return true;

}//load_files()


//Libera a mem�ria e encerra o sistema
void end_app()
{
	//Fecha a fonte
	TTF_CloseFont (font);

	//Libera as surfaces
	SDL_FreeSurface (background);
	for (int i = 0; i < COLORS_AMOUNT; i++)
	{
		SDL_FreeSurface (block_colors[i]);
	}
	SDL_FreeSurface (Sscore);
	SDL_FreeSurface (Sline);

	//Encerra as bibliotecas
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}


											/************************************************/
											/****************Basic Drawing*******************/
											/************************************************/

//Insere um bloco de acordo com a matriz
void insert_block (int x, int y, BLOCK_COLOR color)
{
	if (color != NONE)
	{
		apply_surface ( (x * BLOCK_SIZE + GAME_X), (y * BLOCK_SIZE + GAME_Y), block_colors[(int)color], screen);
	}
}//insert_block

//Insere um bloco na caixa next (com x,y relativo ao interior da caixa)
void insert_next (int x, int y, BLOCK_COLOR color)
{
	if (color != NONE)
	{
		apply_surface ( (x + NEXT_X), (y + NEXT_Y), block_colors[(int)color], screen);
	}
}//insert_next

//Desenha a pontua��o
void print_score (int scoreNum)
{
	SDL_Color cor = {0,0,0};	//Cor RGB(0,0,0)
	char scoreChar[50];			//Score em 'char'

	sprintf_s(scoreChar, "%d", scoreNum);	//Converte o score para 'char'

	//Armazena a surface para o score
	SDL_FreeSurface (Sscore);
	Sscore = TTF_RenderText_Solid (font, scoreChar, cor);

	//Calcula a posi��o do score
	//(este deve ficar alinhado abaixo e a direita da caixa, com 5px de margem)
	int x = SCORE_X + SCORE_WIDTH - Sscore->w - 7;
	int y = SCORE_Y + SCORE_HEIGHT - Sscore->h - 5;

	//Aplica o texto
	apply_surface (x, y, Sscore, screen);
}//print_score


//Desenha a quantidade de linhas
void print_line (int lineNum)
{
	SDL_Color cor = {0,0,0};			//Cor RGB(0,0,0)
	char lineChar[50];					//Line em 'char'

	sprintf_s(lineChar, "%d", lineNum);	//Converte a line para 'char'

	//Armazena a surface para a line
	SDL_FreeSurface (Sline);
	Sline = TTF_RenderText_Solid (font, lineChar, cor);

	//Calcula a posi��o da line
	//(esta deve ficar centralizada na caixa, com 5px de margem para baixo)
	int x = LINE_X + ((LINE_WIDTH - Sline->w) / 2);
	int y = LINE_Y + LINE_HEIGHT - Sline->h - 5;

	//Aplica o texto
	apply_surface (x, y, Sline, screen);
}//print_line


//Desenha o n�vel
void print_level (int levelNum)
{
	SDL_Color cor = {0,0,0};	//Cor RGB(0,0,0)
	char levelChar[50];			//Level em 'char'

	sprintf_s(levelChar, "%d", levelNum);	//Converte o level para 'char'

	//Armazena a surface para a level
	SDL_FreeSurface (Slevel);
	Slevel = TTF_RenderText_Solid (font, levelChar, cor);

	//Calcula a posi��o do level
	//(este deve ficar centralizado na caixa, com 5px de margem para baixo)
	int x = LEVEL_X + ((LEVEL_WIDTH - Slevel->w) / 2);
	int y = LEVEL_Y + LEVEL_HEIGHT - Slevel->h - 5;

	//Aplica o texto
	apply_surface (x, y, Slevel, screen);

}//print_level


//Desenha a matriz
void paint_matrix ()
{
	//Percorre a matriz
	for( int i = 0; i < MATRIX_HEIGHT; i++)
		for( int j = 0; j < MATRIX_WIDTH; j++)
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
		//Percorre cada c�lula dentro da linha
		for (int j = 0; j < MATRIX_WIDTH; j++)
		{
			//Se for a linha mais alta (0) prenche com NONE, se n�o, apenas copia da linha de cima
			game_matrix[i][j] = (i == 0 ? NONE : game_matrix[i-1][j]);
		}//for
	}//for
}//void collapse_line (int line)





//Checa por linhas completas e retorna um vetor no formato:
//{ qtd de linhas, linha 1, linha 2, linha 3, linha 4 }
int* check_lines()
{
	//Armazena as informa��es para retorno
	int* tmp;
	tmp = (int*) malloc( sizeof(int)*5 );
	for (int i = 0; i < 5; i++)
	{
		tmp[i] = 0;
	}//for

	//Armazena a quantidade de blocos por linha
	int filleds = 0;

	//Percorre cada uma das linhas
	for (int i = 0; i < MATRIX_HEIGHT; i++)
	{
		//Percorre cada c�lula dentro da linha
		for (int j = 0; j < MATRIX_WIDTH; j++)
		{
			//Se estiver preenchido
			if (game_matrix[i][j] != NONE)
			{
				//Acrescenta 1 aos filleds
				filleds++;
			}
		}//for (c�lulas)

		//Se todas est�o preenchidas (filleds == 10)
		if (filleds == MATRIX_WIDTH)
		{
			//Armazena no vetor de retorno, na posi��o seguinte
			//Isto depende da quantidade de linhas que j� foram preenchidas
			switch (tmp[0])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				tmp[0] = tmp[0] + 1;
				tmp[tmp[0]] = i;
				break;

			//Se chegar no limite (4) j� retorna para economizar CPU
			//e evitar um acesso indevido � mem�ria
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




int nextsss = 0;
//Gera um tetramino aleat�rio
int get_next()
{
	//return SDL_GetTicks() % 7;
	//Just for tests
	return nextsss++ % 7;

}//int get_next()



}//namespace