#include "ParticleEngine.h"

#include <SDL/SDL.h>
#include <iostream>

using namespace AEON_ENGINE;

ParticleEmitter::ParticleEmitter(int amount_, float lifetime_) :
	m_particleAmount(amount_),
	m_lifetime(lifetime_)
{
	m_elapsedtime = 0.0f;
	m_gravity = -9.8f;
	m_looping = false;
	m_vel = glm::vec3(0.0f, 0.0f, 0.0f);
	m_colour = glm::vec3(1.0f, 0.0f, 0.0f);

	initParticleSystem(true);

	m_timer = new Stopwatch();
}

ParticleEmitter::~ParticleEmitter()
{
	//Empty
}

//Updating and rendering
void ParticleEmitter::update(const float deltaTime_)
{
	m_timer->Update(deltaTime_);
}

void ParticleEmitter::render(Shader* shader_)
{
	//if (m_elapsedtime > m_lifetime)
	//	if (!m_looping) {
	//		isPlaying = false;
	//		return;
	//	}
	//	else if (m_looping)
	//		m_elapsedtime = 0.0f;

	//if (isPlaying) {
	//	m_elapsedtime += 0.01f;

	//	std::cout << m_elapsedtime << std::endl;
	//	shader_->setFloat("time", m_elapsedtime);
	//	shader_->setFloat("gravity", m_gravity);
	//	shader_->setVec4("colour", m_colour);

	//	glBindVertexArray(m_VAO);
	//	glPointSize(5.0f);
	//	glDrawArrays(GL_POINTS, 0, m_particles.size());
	//}

	if (isPlaying) {
		if (m_elapsedtime < m_lifetime) {
			m_elapsedtime = m_timer->getTimerValue();

			//std::cout << m_elapsedtime << std::endl;
			transform.updateModelMatrix();
			shader_->setMat4("model", transform.modelMatrix);
			shader_->setFloat("time", m_elapsedtime * 1.5f);
			shader_->setFloat("gravity", m_gravity);
			shader_->setVec3("colour", m_colour);

			glBindVertexArray(m_VAO);
			glPointSize(2.5f);
			glDrawArrays(GL_POINTS, 0, m_particles.size());
		}
		else {
			m_elapsedtime = 0.0f;

			if (!m_looping)
				isPlaying = false;
			else
				m_timer->StartTimer(m_lifetime);
		}
	}

	//Always good practice to set everything back to defaults once configured
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);

}

void ParticleEmitter::initParticleSystem(bool randomVel)
{
	if (!m_particles.empty())
		m_particles.clear();

	Particle particle;
	Randomizer rand;
	for (int i = 0; i < m_particleAmount; i++) {
		particle.p_pos = glm::vec3(0.0f, 0.0f, 0.0f);

		if (randomVel) {
			particle.p_vel.x = rand.box_muller(0.0, 1.0);
			particle.p_vel.y = std::abs(rand.box_muller(0.0, 3.0));
			particle.p_vel.z = rand.box_muller(0.0, 1.0);
		}
		else {
			particle.p_vel = m_vel;
		}

		m_particles.push_back(particle);
	}

	generateBuffers();
}

void ParticleEmitter::generateBuffers() {
	//Create buffers/arrays
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle), &m_particles[0], GL_STATIC_DRAW);

	//Set the vertex attribute pointers
	//Positions attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)0);
	//Velocity attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, p_vel));

	glBindVertexArray(0);
}

void ParticleEmitter::play()
{
	m_elapsedtime = 0.0f;
	isPlaying = true;
	m_timer->StartTimer(m_lifetime);
}

void ParticleEmitter::stop()
{
	isPlaying = false;
}

void ParticleEmitter::setParticleAmount(int amount_)
{
	m_particleAmount = amount_;
	initParticleSystem(true);
}

void ParticleEmitter::setLifetime(float lifetime_)
{
	m_lifetime = lifetime_;
}

void ParticleEmitter::setLooping(bool loop_)
{
	m_looping = loop_;
}

void ParticleEmitter::setColour(glm::vec3 colour_)
{
	m_colour = colour_;
}

void ParticleEmitter::setVelocity(glm::vec3 velocity_)
{
	m_vel = velocity_;
	initParticleSystem(false);
}

void ParticleEmitter::setGravity(float gravity_)
{
	m_gravity = gravity_;
}