#ifndef _LC_TETRAMINOS_H_
#define _LC_TETRAMINOS_H_

#include "Tetramino.h"

namespace line_collapser
{

/********************************************************/
/************************** I ***************************/
/********************************************************/

	class I: public Tetramino
	{
	public:
		I();
		void draw_in_next();
		void reset();
	}; //class Line

/********************************************************/
/************************** O ***************************/
/********************************************************/

	class O: public Tetramino
	{
	public:
		O();
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
/************************** J ***************************/
/********************************************************/

	class J: public Tetramino
	{
	public:
		J();
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
/************************** Z ***************************/
/********************************************************/

	class Z: public Tetramino
	{
	public:
		Z();
		void draw_in_next();
		void reset();
	}; //class ReverseS

/********************************************************/
/************************** T ***************************/
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
