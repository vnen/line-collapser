#include "Tetramino.h"

namespace line_collapser
{
	//Constructor
	Tetramino::Tetramino()
	{
		//Sets the initial values for attributes
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;
		this->x = -1;
		this->y =  3;

		this->reseted = true;

		this->cor = NONE;

	}//Tetramino::Tetramino()





	/* Puts Tetramino inside the game matrix
	 * if 'force' is 'true', puts even if the position is occupied or out of the matrix
	 * returns 'false' tried to put in an occupied position
	 */
	bool Tetramino::put_in_matrix(bool force)
	{
		bool flag = true;

		if (!force)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					//If x + i or y + i  is negative, still is out of game matrix
					if (((this->x + i) < 0) || ((this->y + j) < 0))
					{
						if (matrix[i][j] == 1)
						{
							return false;
						}//if
					}//if
					//If x + i or y + i is greater than limit, it is too out of matrix
					if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					{
						if (matrix[i][j] == 1)
						{
							return false;
						}//if
					}//if

					if (this->matrix[i][j] == 1)
					{
						if (game_matrix[this->x + i][this->y + j] != NONE)
						{
							return false;
						}//if
					}//if
				}//for
		}//if !force

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//If x + i or y + i  is negative, still is out of game matrix
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//If x + i or y + i is greater than limit, it is too out of matrix
				if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						flag = false;
					}//if
					game_matrix[this->x + i][this->y + j] = this->cor;
				}//if
			}//for

		this->reseted = false;
		return flag;

	}//bool put_in_matrix();





	/* Moves down
	 * returns 'false' if it can't move to that direction
	 */
	bool Tetramino::move_down()
	{
		//If it is reseted, it isn't possible to move (it isn't on the matrix)
		if (this->reseted) return false;

		bool flag = true;
		
		/*:
			Removes it from game matrix
			Increments vertical position (x)
			Check for collisions using 'put_in_matrix(false)'
			If there are collisions
				Decrements vertical position (x)
				Puts it again on matrix
				Returns 'false'
			If there are not
				Already put using 'put_in_matrix(false)'
				Returns 'true'
		 */

		//Removes it from game matrix (the inverse of 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//If x + i or y + i  is negative, still is out of game matrix
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//If x + i or y + i is greater than limit, it is too out of matrix
				if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		//Increments vertical position (x)
		this->x++;

		//Check for collisions using 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//If there are collisions
		if (!flag)
		{
			//Decrements vertical position (x)
			this->x--;

			//Puts it again on matrix
			//(without 'force'. Ttechnically, the space was emptied,
			//so, even without forcing, the function must have success, or else we have an unknown error [buffer overflow could cause that])
			if (!this->put_in_matrix(false)) return false;

			//Returns 'false'
			return false;
		}//if
		//If there are not
		else
		{
			//Already put using 'put_in_matrix(false)'
			//Returns 'true'
			return true;
		}//else

	}//bool Tetramino::move_down();





	/* Moves left
	 * returns 'false' if it can't move to that direction
	 */
	bool Tetramino::move_left()
	{
		//If it is reseted, it isn't possible to move (it isn't on the matrix)
		if (this->reseted) return false;

		bool flag = true;
		
		/*:
			Removes it from game matrix
			Decrements horizontal position (y)
			Check for collisions using 'put_in_matrix(false)'
			If there are collisions
				Increments horizontal position (y)
				Puts it again on matrix
				Returns 'false'
			If there are not
				Already put using 'put_in_matrix(false)'
				Returns 'true'
		 */

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		this->y--;

		flag = this->put_in_matrix(false);

		if (!flag)
		{
			this->y++;

			if (!this->put_in_matrix(false)) return false;

			return false;
		}//if
		else
		{
			return true;
		}//else

	}//bool Tetramino::move_left()





	/* Moves right
	 * returns 'false' if it can't move to that direction
	 */
	bool Tetramino::move_right()
	{
		//If it is reseted, it isn't possible to move (it isn't on the matrix)
		if (this->reseted) return false;

		bool flag = true;
		
		/*:
			Removes it from game matrix
			Increments horizontal position (y)
			Check for collisions using 'put_in_matrix(false)'
			If there are collisions
				Decrements horizontal position (y)
				Puts it again on matrix
				Returns 'false'
			If there are not
				Already put using 'put_in_matrix(false)'
				Returns 'true'
		 */

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		this->y++;

		flag = this->put_in_matrix(false);

		if (!flag)
		{
			this->y--;

			if (!this->put_in_matrix(false)) return false;

			return false;
		}//if
		else
		{
			return true;
		}//else

	}//bool Tetramino::move_right()





	/* Rotate counter-clockwise
	 * returns 'false' if it can't rotate
	 */
	bool Tetramino::rotate()
	{
		//If it is reseted, it isn't possible to move (it isn't on the matrix)
		if (this->reseted) return false;

		/*
			 * Makes a copy of game matrix
			 * Removes from game matrix
			 * If Tetramino is in it final state
			 *		Makes a copy of coordinates
			 *		Does a 'reset()'
			 *		Updates coordinates and reseted state
			 * If it isn't
			 *		Rotate the original matrix
			 * Check for collisions using 'put_in_matrix(false)'
			 * If there are collisions:
			 *		Copy from backup to matrix (undoing the rotation)
			 *		Put it again on matrix
			 *		Returns 'false'
			 * If there aren't:
			 *		Already put using 'put_in_matrix(false)'
			 *		Updates the actual state (orientation)
			 *		Returns 'true'
			 */

		unsigned short int backup[4][4];
		int i;
		int j;

		//Making the copy and removing from game matrix in the same loop
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				backup[i][j] = this->matrix[i][j];

				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				if (((this->x + i) >= LC_MATRIX_HEIGHT) || ((this->y + j) >= LC_MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		if (this->state == this->max_states)
		{
			i = this->x;
			j = this->y;

			this->reset();

			this->x = i;
			this->y = j;
			this->reseted = false;
		}//if
		
		else
		{
		/* Rotate the original matrix
		 * We do it with the following formulas:
		 * x' = x * cos(theta) - y * sin(theta)
		 * y' = x * sin(theta) + y * cos(theta)
		 * With theta = 90 degrees (pi/2):
		 * x' = -y
		 * y' = x
		 */
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				this->matrix[i][j] = backup[3-j][i];
			}//for
		}//else

		bool flag = this->put_in_matrix(false);
		if (!flag)
		{
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					this->matrix[i][j] = backup[i][j];
				}//for

			if (!this->put_in_matrix(false)) return false;

			return false;
		}//if

		else
		{
			//If it got the limit, go back to the initial
			if (this->state == this->max_states)
				this->state = 1;
			//If it didn't, increments
			else
				this->state = this->state + 1;

			return true;
		}
	}//bool Tetramino::rotate()

}//namespace
