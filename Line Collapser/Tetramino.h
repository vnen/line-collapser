#ifndef _LC_TETRAMINO_H_
#define _LC_TETRAMINO_H_

#include "includes.h"

namespace line_collapser
{
	/* I know they're called Tetriminos, but it is not Tetris so I can call it the way I want to  =P
	 * This abstract class it's used as base
	 * to the creation of each form of Tetraminos
	 */

class Tetramino //abstract
{
protected:
	unsigned short int matrix[4][4];
	lcBlockColor cor;
	int x, y; //position of Tetramino matrix inside the game matrix
	//Max of states (orientations) of the Tetramino
	unsigned short int max_states;
	//Actult o state
	unsigned short int state;
	//If it is in construction state
	bool reseted;

public:
	//Constructor
	Tetramino();

	/* Puts Tetramino inside the game matrix
	 * if 'force' is 'true', puts even if the position is occupied or out of the matrix
	 * returns 'false' tried to put in an occupied position
	 */
	bool put_in_matrix(bool force);

	/* Moves down
	 * returns 'false' if it can't move to that direction
	 */
	bool move_down();

	/* Moves left
	 * returns 'false' if it can't move to that direction
	 */
	bool move_left();

	/* Moves right
	 * returns 'false' if it can't move to that direction
	 */
	bool move_right();

	/* Rotate counter-clockwise
	 * returns 'false' if it can't rotate
	 */
	bool rotate();

	//Draws the Tetramino on the 'next' box
	virtual void draw_in_next() = 0;

	//Empties the matrix
	virtual void reset() = 0;

};//class
}//namespace

#endif
