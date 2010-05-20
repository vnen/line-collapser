#ifndef _FALLING_TETRAMINOS_H_
#define _FALLING_TETRAMINOS_H_

#include "includes.h"
#include "Tetramino.h"

namespace falling_hell
{

/********************************************************/
/*********************** L i n e ************************/
/********************************************************/

	class Line: public Tetramino
	{
	public:
		Line();
		void draw_in_next();
		void reset();
	}; //class Line

/********************************************************/
/********************* S q u a r e **********************/
/********************************************************/

	class Square: public Tetramino
	{
	public:
		Square();
		void draw_in_next();
		void reset();
	}; //class Square

/********************************************************/
/************************** L ***************************/
/********************************************************/

	class L: public Tetramino
	{
	public:
		L();
		void draw_in_next();
		void reset();
	}; //class L

/********************************************************/
/******************* R e v e r s e L ********************/
/********************************************************/

	class ReverseL: public Tetramino
	{
	public:
		ReverseL();
		void draw_in_next();
		void reset();
	}; //class ReverseL

/********************************************************/
/************************** S ***************************/
/********************************************************/

	class S: public Tetramino
	{
	public:
		S();
		void draw_in_next();
		void reset();
	}; //class S

/********************************************************/
/******************* R e v e r s e S ********************/
/********************************************************/

	class ReverseS: public Tetramino
	{
	public:
		ReverseS();
		void draw_in_next();
		void reset();
	}; //class ReverseS

/********************************************************/
/************************** S ***************************/
/********************************************************/

	class T: public Tetramino
	{
	public:
		T();
		void draw_in_next();
		void reset();
	}; //class T

}//namespace

#endif