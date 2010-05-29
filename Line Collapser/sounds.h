/*
 * sounds.h
 *
 *  Created on: 28/05/2010
 *      Author: George Marques
 */

#ifndef _LC_SOUNDS_H_
#define _LC_SOUNDS_H_

//Constants
#define LC_MUSIC_STOPPED	0
#define LC_MUSIC_PLAYING	1
#define LC_MUSIC_PAUSED		2


namespace line_collapser
{

//Plays the game background music (actually, a metal remix of Tetris' music)
bool playMainBgm();

//Plays the start screen's bgm
bool playStartBgm();

//Plays a specific sound effect (of the list I'll make when I have the sound)
bool playEffect(int effect);

//Pauses music
//Returns the playing state after the function runs
int musicTogglePause();

/* Find out the filename for the sound effect number
 */
char* whichSound(int fx);

}//namespace

#endif /* _LC_SOUNDS_H_ */
