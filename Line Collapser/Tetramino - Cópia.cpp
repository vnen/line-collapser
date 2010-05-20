#include "Tetramino.h"

namespace falling_hell
{
	//Construtor
	Tetramino::Tetramino()
	{
		//Zera os atributos
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		this->cor = NONE;

	}//Tetramino::Tetramino()


	//Coloca o tetramino na matiz do jogo
	//devolve 'false' se tentar colocar em posição já ocupada
	//se force for 'true' coloca na posição, mesmo se já ocupada
	bool Tetramino::put_in_matrix(bool force)
	{
		bool flag = true;

		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
			{
				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[i][j] != NONE)
					{
						flag = false;
						if (force) game_matrix[i][j] = this->cor;
					}//if
					else
					{
						game_matrix[i][j] = this->cor;
					}//else
				}
			}//for

		return flag;

	}//bool put_in_matrix();

	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta direção
	bool Tetramino::move_down()
	{
		//No primeiro laço checamos se é possível mover
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
			{
				if (this->matrix[i][j] == 1)
				{
					//Se já estivermos na base da matriz, não é possível mover
					if (i == MATRIX_HEIGHT - 1)
					{
						return false;
					}//if
					else if (game_matrix[i+1][j] != NONE)
					{
						return false;
					}//else if
				}//if
			}//for

		//No segundo laço movemos toda a matriz para baixo
		for (int i = MATRIX_HEIGHT - 1; i > 0 ; i--)
			for (int j = 1; j < MATRIX_WIDTH; j++)
			{
				if (this->matrix[i-1][j] == 1)
				{
					this->matrix[i-1][j] = 0;
					this->matrix[i][j] = 1;

					game_matrix[i-1][j] = NONE;
					game_matrix[i][j] = this->cor;
				}//if
			}//for

		return true;
	}//bool move_down();

}//namespace