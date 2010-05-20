#ifndef _FALLING_TETRAMINO_H_
#define _FALLING_TETRAMINO_H_

#include "includes.h"

namespace falling_hell
{
	/* Esta classe não é instanciável, serve como base para
	 * a criação de Tetraminos individuais
	 */

class Tetramino abstract
{
protected:
	unsigned short int matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
	BLOCK_COLOR cor;

public:
	//Construtor
	Tetramino();

	//Coloca o tetramino na matiz do jogo
	//devolve 'false' se tentar colocar em posição já ocupada
	bool put_in_matrix(bool force);

	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta direção
	bool move_down();

	//Desenha o tetramino na caixa NEXT
	virtual void draw_in_next() = 0;

	//Zera a matriz
	virtual void reset() = 0;

};//class
}//namespace

#endif