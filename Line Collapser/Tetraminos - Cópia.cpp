#include "Tetraminos.h"

namespace falling_hell
{

/********************************************************/
/*********************** L i n e ************************/
/********************************************************/

	Line::Line()
	{
		this->cor = BLACK;
		this->matrix[0][3] = 1;
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;
	}//Line::Line()

	void Line::draw_in_next()
	{
		insert_next ((NEXT_WIDTH / 2) - (2 * BLOCK_SIZE), (NEXT_HEIGHT - BLOCK_SIZE) / 2, this->cor);
		insert_next ((NEXT_WIDTH / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT - BLOCK_SIZE) / 2, this->cor);
		insert_next ((NEXT_WIDTH / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT - BLOCK_SIZE) / 2, this->cor);
		insert_next ((NEXT_WIDTH / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT - BLOCK_SIZE) / 2, this->cor);

	}//void Line::draw_in_next()

	void Line::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][3] = 1;
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;

	}//void Line::reset()

/********************************************************/
/********************* S q u a r e **********************/
/********************************************************/

	Square::Square()
	{
		this->cor = BLUE;
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
	}//Square::Square()

	void Square::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 0 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 0 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 0 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 0 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//void Square::draw_in_next()

	void Square::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;

	}//void Square::reset()

/********************************************************/
/************************** L ***************************/
/********************************************************/

	L::L()
	{
		this->cor = GREEN;
		this->matrix[0][6] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;
	}//L::L()

	void L::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//L::void draw_in_next()

	void L::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][6] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;

	}//void L::reset()

/********************************************************/
/******************* R e v e r s e L ********************/
/********************************************************/

	ReverseL::ReverseL()
	{
		this->cor = NAVY;
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;
		this->matrix[1][6] = 1;
	}//ReverseL::ReverseL()

	void ReverseL::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//ReverseL::void draw_in_next()

	void ReverseL::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;
		this->matrix[1][6] = 1;

	}//void ReverseL::reset()

/********************************************************/
/************************** S ***************************/
/********************************************************/

	S::S()
	{
		this->cor = RED;
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
	}//S::S()

	void S::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//S::void draw_in_next()

	void S::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][5] = 1;
		this->matrix[0][6] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;

	}//void S::reset()

/********************************************************/
/******************* R e v e r s e S ********************/
/********************************************************/

	ReverseS::ReverseS()
	{
		this->cor = VIOLET;
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;
	}//ReverseS::ReverseS()

	void ReverseS::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//ReverseS::void draw_in_next()

	void ReverseS::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][4] = 1;
		this->matrix[0][5] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;

	}//void ReverseS::reset()

/********************************************************/
/************************** T ***************************/
/********************************************************/

	T::T()
	{
		this->cor = YELLOW;
		this->matrix[0][5] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;
	}//T::T()

	void T::draw_in_next()
	{
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (1 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) - (0 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);
		insert_next (((NEXT_WIDTH - 1 * BLOCK_SIZE) / 2) + (1 * BLOCK_SIZE), (NEXT_HEIGHT / 2) - (0 * BLOCK_SIZE), this->cor);

	}//T::void draw_in_next()

	void T::reset()
	{
		//Zera a matriz
		for (int i = 0; i < MATRIX_HEIGHT; i++)
			for (int j = 0; j < MATRIX_WIDTH; j++)
				this->matrix[i][j] = 0;

		//Reinicia a posição
		this->matrix[0][5] = 1;
		this->matrix[1][4] = 1;
		this->matrix[1][5] = 1;
		this->matrix[1][6] = 1;

	}//void T::reset()

}//namespace