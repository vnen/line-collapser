#ifndef _FALLING_TETRAMINO_H_
#define _FALLING_TETRAMINO_H_

#include "includes.h"

namespace falling_hell
{
	/* Esta classe n�o � instanci�vel, serve como base para
	 * a cria��o de Tetraminos individuais
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
	//devolve 'false' se tentar colocar em posi��o j� ocupada
	bool put_in_matrix(bool force);

	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool move_down();

	//Desenha o tetramino na caixa NEXT
	virtual void draw_in_next() = 0;

	//Zera a matriz
	virtual void reset() = 0;

};//class
}//namespace

#endif