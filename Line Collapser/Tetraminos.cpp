#include "includes.h"
#include "Tetraminos.h"

namespace line_collapser
{

/********************************************************/
/************************** I ***************************/
/********************************************************/

	I::I()
	{
		this->cor = BLACK;
		this->max_states = 2;
		this->state = 1;
		this->matrix[1][0] = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
	}//I::I()

	void I::draw_in_next()
	{
		insert_next ((LC_NEXT_WIDTH / 2) - (2 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT - LC_BLOCK_SIZE) / 2, this->cor);
		insert_next ((LC_NEXT_WIDTH / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT - LC_BLOCK_SIZE) / 2, this->cor);
		insert_next ((LC_NEXT_WIDTH / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT - LC_BLOCK_SIZE) / 2, this->cor);
		insert_next ((LC_NEXT_WIDTH / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT - LC_BLOCK_SIZE) / 2, this->cor);

	}//void I::draw_in_next()

	void I::reset()
	{
		//Empties the matrix
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		//Resets position
		this->x = -1;
		this->y =  3;
		//Resets orientation
		this->matrix[1][0] = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;

		//Set as reseted
		this->reseted = true;

	}//void I::reset()

/********************************************************/
/************************** O ***************************/
/********************************************************/

	O::O()
	{
		this->cor = BLUE;
		this->max_states = 1;
		this->state = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[2][1] = 1;
		this->matrix[2][2] = 1;
	}//O::O()

	void O::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 0 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 0 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 0 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 0 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);

	}//void O::draw_in_next()

	void O::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[2][1] = 1;
		this->matrix[2][2] = 1;

		this->reseted = true;

	}//void O::reset()

/********************************************************/
/************************** L ***************************/
/********************************************************/

	L::L()
	{
		this->cor = GREEN;
		this->max_states = 4;
		this->state = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][1] = 1;
	}//L::L()

	void L::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);

	}//L::void draw_in_next()

	void L::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][1] = 1;

		this->reseted = true;

	}//void L::reset()

/********************************************************/
/************************** J ***************************/
/********************************************************/

	J::J()
	{
		this->cor = NAVY;
		this->max_states = 4;
		this->state = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][3] = 1;
	}//J::J()

	void J::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);

	}//J::void draw_in_next()

	void J::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][3] = 1;

		this->reseted = true;

	}//void J::reset()

/********************************************************/
/************************** S ***************************/
/********************************************************/

	S::S()
	{
		this->cor = RED;
		this->max_states = 2;
		this->state = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][1] = 1;
		this->matrix[2][2] = 1;
	}//S::S()

	void S::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);

	}//S::void draw_in_next()

	void S::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][1] = 1;
		this->matrix[2][2] = 1;

		this->reseted = true;

	}//void S::reset()

/********************************************************/
/************************** Z ***************************/
/********************************************************/

	Z::Z()
	{
		this->cor = VIOLET;
		this->max_states = 2;
		this->state = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[2][2] = 1;
		this->matrix[2][3] = 1;
	}//Z::Z()

	void Z::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);

	}//Z::void draw_in_next()

	void Z::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[2][2] = 1;
		this->matrix[2][3] = 1;

		this->reseted = true;

	}//void Z::reset()

/********************************************************/
/************************** T ***************************/
/********************************************************/

	T::T()
	{
		this->cor = YELLOW;
		this->max_states = 4;
		this->state = 1;
		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][2] = 1;
	}//T::T()

	void T::draw_in_next()
	{
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (0 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) - (0 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);
		insert_next (((LC_NEXT_WIDTH - 1 * LC_BLOCK_SIZE) / 2) + (1 * LC_BLOCK_SIZE), (LC_NEXT_HEIGHT / 2) - (1 * LC_BLOCK_SIZE), this->cor);

	}//T::void draw_in_next()

	void T::reset()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;

		this->x = -1;
		this->y =  3;

		this->matrix[1][1] = 1;
		this->matrix[1][2] = 1;
		this->matrix[1][3] = 1;
		this->matrix[2][2] = 1;

		this->reseted = true;

	}//void T::reset()

}//namespace
