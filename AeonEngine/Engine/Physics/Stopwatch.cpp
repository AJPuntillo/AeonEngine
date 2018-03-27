#include "Stopwatch.h"
#include <iostream>
using namespace AEON_ENGINE;

Stopwatch::Stopwatch()
{
	//Empty
}

Stopwatch::~Stopwatch()
{
	//Emtpy
}

void Stopwatch::StartTimer(float duration_)
{
	m_duration = duration_;
	m_timer = 0.0f;
	m_isRunning = true;
}

void Stopwatch::Update(float deltaTime_)
{
	if (m_isRunning) {
		m_timer += deltaTime_;
	}

	if (m_timer >= m_duration) {
		m_isRunning = false;
		m_timer = m_duration;
	}
}

float Stopwatch::getTimerValue()
{
	return m_timer;
}

float Stopwatch::getAlphaValue()
{
	float tmp = m_timer / m_duration;
	return tmp;
}

void Stopwatch::ResetTimer()
{
	m_timer = 0.0f;
}
glm::vec3 tmp;
glm::vec3 Stopwatch::LerpTo(glm::vec3 startPos_, glm::vec3 endPos_)
{
	if (m_isRunning) {
		tmp = glm::lerp(startPos_, endPos_, getAlphaValue());
	}

	return tmp;
}