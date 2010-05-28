/*
 * sounds.cpp
 *
 *  Created on: 28/05/2010
 *      Author: George Marques
 */

#include "includes.h"

namespace line_collapser
{

//Plays the game background music (actually, a metal remix of Tetris' music)
//Returns the success status
bool playMainBgm()
{
	//If there isn't a bgm loaded
	if (bgm == NULL)
		{ return false; } //Returns a error

	//Plays the bgm forever
	//And checks for error
	if (Mix_PlayMusic(bgm, -1) == -1)
		{ return false; }

} //bool playMainBgm()

}//namespace
