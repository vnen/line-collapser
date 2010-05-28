/*
 * sounds.cpp
 *
 *  Created on: 28/05/2010
 *      Author: George Marques
 */

#include "includes.h"
#include "sounds.h"

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

	return true;

} //bool playMainBgm()





//Pauses music
//Returns the playing state after the function runs
int musicTogglePause()
{
	//If music is playing (it may be paused, but not stopped)
	if (Mix_PlayingMusic() == 1)
	{
		//If music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume music
			Mix_ResumeMusic();
			return LC_MUSIC_PLAYING;
		}
		//If music isn't paused
		else
		{
			//Pause music
			Mix_PauseMusic();
			return LC_MUSIC_PAUSED;
		}
	}

	return LC_MUSIC_STOPPED;

} //void musicTogglePause()

}//namespace
