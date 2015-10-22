/*
 * sounds.cpp
 *
 *  Created on: 28/05/2010
 *      Author: George Marques
 */

#include "includes.h"
#include "sounds.h"
#include <string>

namespace line_collapser
{

//Plays the game background music (actually, a metal remix of Tetris' music)
//Returns the success status
bool playMainBgm()
{
	//If there isn't a bgm loaded
	if (sndBgm == NULL)
		{ return false; } //Returns a error

	//Plays the bgm forever
	//And checks for error
	if (Mix_PlayMusic(sndBgm, -1) == -1)
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





Mix_Chunk* sndFX = NULL;
int whichEffect = LC_SOUND_FX_NONE;

//Plays a specific sound effect (of the list made on "includes.h")
void playEffect(int effect)
{
	//If the sound is already loaded, we don't need to load it again
	if (whichEffect == effect && effect != LC_SOUND_FX_NONE)
	{
		Mix_PlayChannel(-1, sndFX, 0);
		return;
	}

	//Frees the file
	Mix_FreeChunk(sndFX);

	//Loads sound file based on selected effect
	switch (effect)
	{
	case LC_SOUND_FX_COLLAPSE:
		sndFX = Mix_LoadWAV("sounds/collapse.ogg");
		break;

	case LC_SOUND_FX_LAND:
		sndFX = Mix_LoadWAV("sounds/land.ogg");
		break;

	default:
		return;
		break;

	} //switch (effect)

	if (sndFX != NULL)
	{
		//Stores which effect is already loaded
		whichEffect = effect;

		//Plays effect if it was loaded
		Mix_PlayChannel(-1, sndFX, 0);
	}
	else
	{
		//Nothing is loaded
		whichEffect = LC_SOUND_FX_NONE;
	}

} //void playEffect(int effect)





//Plays the start screen's bgm
bool playStartBgm()
{
	//If there isn't a bgm loaded
	if (sndStartBgm == NULL)
		{ return false; } //Returns a error

	//Plays the bgm forever
	//And checks for error
	if (Mix_PlayMusic(sndStartBgm, -1) == -1)
		{ return false; }

	return true;

}//bool playStartBgm()
}//namespace
