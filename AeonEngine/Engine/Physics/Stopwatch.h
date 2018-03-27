#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <glm/gtx/compatibility.hpp>

namespace AEON_ENGINE {

	class Stopwatch
	{
	public:
		Stopwatch();
		~Stopwatch();

		void StartTimer(float duration_);
		void Update(float deltaTime_);
		float getTimerValue();
		float getAlphaValue();
		void ResetTimer();

		//Lerps and returns the Vec3 at a certain time
		glm::vec3 LerpTo(glm::vec3 startPos_, glm::vec3 endPos_);

		float getDuration() { return m_duration; }
		bool IsTimerRunning() { return m_isRunning; };
		float m_timer;

	private:
		float m_duration;
		bool m_isRunning = false;
	};

}

#endif

