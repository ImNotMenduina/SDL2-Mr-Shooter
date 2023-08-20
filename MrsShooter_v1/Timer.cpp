#include "Timer.h"
using namespace TimerClass;

Timer::Timer()
{
	this->isStarted = false;
	this->isPaused = false;
	this->timePause = 0;
	this->timeStart = 0;
}

void Timer::Start()
{
	this->isStarted = true;
	this->isPaused = false;

	this->timeStart = SDL_GetTicks();
	this->timePause = 0;
}

void Timer::Stop()
{
	this->isStarted = false;
	this->isPaused = false;
	this->timePause = 0;
	this->timeStart = 0;
}

void Timer::Pause()
{
	if (this->isStarted)
	{
		this->isPaused = true;

		//relative time paused
		this->timePause = SDL_GetTicks() - this->timeStart;

		this->isStarted = false;
		this->timeStart = 0;
	}
}

void Timer::Unpause()
{
	if (this->isPaused && !this->isStarted)
	{
		this->isStarted = true;
		this->timeStart = SDL_GetTicks() - this->timePause;
		this->isPaused = false;
		this->timePause = 0;
	}
}

unsigned int Timer::getTicks()
{
	if (this->isPaused)
	{
		return this->timePause;
	}
	else
	{
		return SDL_GetTicks() - this->timeStart;
	}
}

bool Timer::checkIsPaused()
{
	return this->isPaused;
}

bool Timer::checkIsStarted()
{
	return this->isStarted;
}