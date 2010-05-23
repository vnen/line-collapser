#ifndef _FALLING_TETRAMINO_H_
#define _FALLING_TETRAMINO_H_

#include "includes.h"

namespace line_collapser
{
	/* Esta classe nXo X instanciXvel, serve como base para
	 * a criaXXo de Tetraminos individuais
	 */

class Tetramino
{
protected:
	unsigned short int matrix[4][4];
	BLOCK_COLOR cor;
	int x, y; //posiXXo da matriz do Tetramino dentro da matriz principal do jogo
	//MXximo de estados (orientaXXes) possXveis
	unsigned short int max_states;
	//Estado atual
	unsigned short int state;
	//Se estX no estado inicial
	bool reseted;

public:
	//Construtor
	Tetramino();

	//Coloca o tetramino na matiz do jogo
	//devolve 'false' se tentar colocar em posiXXo jX ocupada
	bool put_in_matrix(bool force);

	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool move_down();

	//Move para a esquerda
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool move_left();

	//Move para a direita
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool move_right();

	//Gira no sentido anti-horXrio
	//Devolve 'false' se nao pode rotacionar
	bool rotate();

	//Desenha o tetramino na caixa NEXT
	virtual void draw_in_next() = 0;

	//Zera a matriz
	virtual void reset() = 0;

};//class
}//namespace

#endif
