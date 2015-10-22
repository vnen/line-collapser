#ifndef _LC_TIMER_H_
#define _LC_TIMER_H_

namespace line_collapser
{

class Timer
{

private:
	int ticks;

	bool started;
	bool paused;

public:
	Timer();

	void start();
	void togglePause();
	void stop();

	int getTicks();

	bool isStarted();
	bool isPaused();

};
}
#endif
