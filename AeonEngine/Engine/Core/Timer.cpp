#include "Timer.h"

#include <SDL/SDL.h>

using namespace AEON_ENGINE;

Timer::Timer()
{
	//Empty
}

Timer::~Timer()
{
	//Empty
}

void Timer::updateFrameTicks()
{
	m_prevTicks = m_currTicks;
	m_currTicks = SDL_GetTicks();
}

void Timer::startTimer()
{
	m_prevTicks = SDL_GetTicks();
	m_currTicks = SDL_GetTicks();
}

float Timer::getDeltaTime() const
{
	return (m_currTicks - m_prevTicks) / 1000.0f;
}

unsigned int Timer::getSleepTime(const unsigned int fps) const
{
	unsigned int milliSecsPerFrame = 1000 / fps;
	if (milliSecsPerFrame == 0) {
		return 0;
	}

	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - m_currTicks);
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}

	return sleepTime;
}