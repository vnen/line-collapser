#include "SDL.h"
#include "Timer.h"

namespace line_collapser
{

Timer::Timer()
{
	this->ticksOnPause = 0;
	this->ticksOnStart = 0;
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
		return this->ticksOnPause;
	}
	else
	{
		return SDL_GetTicks() - this->ticksOnStart;
	}
}

void Timer::start()
{
	this->started = true;
	this->paused = false;
	this->ticksOnStart = SDL_GetTicks();
}

void Timer::togglePause()
{
	if (this->isStarted())		
		//Se tiver iniciado e ...
		if (!this->isPaused())
			//... não estiver pausado
			//armazena os ticks e pausa o timer
		{
			this->paused = true;
			this->ticksOnPause = SDL_GetTicks() - this->ticksOnStart;	//Acho que uma variável apenas é suficiente para armazenar os ticks 
																		//Como elas trocam entre si, posso usar a mesma e ainda facilita
																		//o código da pausa/continuação do timer
		}
		else
			//... estiver pausado
			//... trocas os ticks e continua com o timing
		{
			this->paused = false;
			this->ticksOnStart = SDL_GetTicks() - this->ticksOnPause;
		}
}

void Timer::stop()
{
	this->started = false;
	this->paused = false;
	this->ticksOnStart = 0;
	this->ticksOnPause = 0;
}

}