#include <SDL/SDL.h>
#include "Timer.h"

namespace line_collapser
{

Timer::Timer()
{
	this->ticks = 0;
	this->paused = false;
	this->started = false;
}


bool Timer::isPaused()
{
	return this->paused;
}

bool Timer::isStarted()
{
	return this->started;
}

int Timer::getTicks()
{
	if (this->isPaused())
	{
		return this->ticks;
	}
	else
	{
		return SDL_GetTicks() - this->ticks;
	}
}

void Timer::start()
{
	this->started = true;
	this->paused = false;
	this->ticks = SDL_GetTicks();
}

void Timer::togglePause()
{
	if (this->isStarted())
	{
		this->paused = !this->paused;
		this->ticks = SDL_GetTicks() - this->ticks;
	}
}

void Timer::stop()
{
	this->started = false;
	this->paused = false;
	this->ticks = 0;
}

}
