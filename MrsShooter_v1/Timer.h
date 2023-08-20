#ifndef Timer_H
#define Timer_H
#include <SDL.h>

namespace TimerClass
{
	class Timer
	{
	private:
		bool isPaused;
		bool isStarted;
		unsigned int timeStart;
		unsigned int timePause;
	public:
		Timer();

		bool checkIsPaused();
		bool checkIsStarted();

		void Start();
		void Stop();
		void Pause();
		void Unpause();

		unsigned int getTicks();
	};
}

#endif