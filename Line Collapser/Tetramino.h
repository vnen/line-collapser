#ifndef _FALLING_TETRAMINO_H_
#define _FALLING_TETRAMINO_H_

#include "includes.h"

namespace line_collapser
{
	/* Esta classe n�o � instanci�vel, serve como base para
	 * a cria��o de Tetraminos individuais
	 */

class Tetramino abstract
{
protected:
	unsigned short int matrix[4][4];
	BLOCK_COLOR cor;
	int x, y; //posi��o da matriz do Tetramino dentro da matriz principal do jogo
	//M�ximo de estados (orienta��es) poss�veis
	unsigned short int max_states;
	//Estado atual
	unsigned short int state;
	//Se est� no estado inicial
	bool reseted;

public:
	//Construtor
	Tetramino();

	//Coloca o tetramino na matiz do jogo
	//devolve 'false' se tentar colocar em posi��o j� ocupada
	bool put_in_matrix(bool force);

	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool move_down();

	//Move para a esquerda
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool move_left();

	//Move para a direita
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool move_right();

	//Gira no sentido anti-hor�rio
	//Devolve 'false' se nao pode rotacionar
	bool rotate();

	//Desenha o tetramino na caixa NEXT
	virtual void draw_in_next() = 0;

	//Zera a matriz
	virtual void reset() = 0;

};//class
}//namespace

#endif