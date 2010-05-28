/*
 * sounds.h
 *
 *  Created on: 28/05/2010
 *      Author: George Marques
 */

#ifndef _LC_SOUNDS_H_
#define _LC_SOUNDS_H_

namespace line_collapser
{

//Plays the game background music (actually, a metal remix of Tetris' music)
bool playMainBgm();

//Plays the start screen's bgm
bool playStartBgm();

//Plays a specific sound effect (of the list I'll make when I have the sound)
bool playEffect(int effect);

}//namespace

#endif /* _LC_SOUNDS_H_ */
