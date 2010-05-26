#ifndef _LC_TIMER_H_
#define _LC_TIMER_H_

namespace line_collapser
{

class Timer
{

private:
	int ticksOnStart;
	int ticksOnPause;

	bool started;
	bool paused;

public:
	Timer();

	void start(); //Inicia o timer
	void togglePause(); //Pausa/despausa o Timer
	void stop();

	int getTicks();

	bool isStarted();
	bool isPaused();

};
}
#endif
