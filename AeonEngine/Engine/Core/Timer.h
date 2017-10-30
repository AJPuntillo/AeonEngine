#ifndef TIMER_H
#define TIMER_H

namespace AEON_ENGINE {

	class Timer {
	public:
		Timer();
		~Timer();

		void startTimer();
		void updateFrameTicks();

		//Getters
		float getDeltaTime() const;
		unsigned int getSleepTime(const unsigned int fps) const;

	private:
		unsigned int m_prevTicks;
		unsigned int m_currTicks;
	};

}

#endif