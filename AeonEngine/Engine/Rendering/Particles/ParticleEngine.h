#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../3D/Entity.h"
#include "../3D/Transform.h"
#include "../../Math/Randomizer.h"
#include "../../Physics/Stopwatch.h"

namespace AEON_ENGINE {

	struct Particle {
		glm::vec3 p_pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 p_vel = glm::vec3(0.0f, 0.0f, 0.0f);
	};

	class ParticleEmitter : public Entity {
	public:
		ParticleEmitter() {};
		ParticleEmitter(int amount_, float lifetime_);
		~ParticleEmitter();

		//Updating and rendering
		void update(const float deltaTime_) override;
		void render(Shader* shader_) override;

		//Initialization
		void initParticleSystem(bool randomVel = false);
		void generateBuffers();

		void play();
		void stop();

		void setParticleAmount(int amount_);
		void setLifetime(float lifetime_);
		void setLooping(bool loop_);
		void setColour(glm::vec3 colour_);
		void setVelocity(glm::vec3 velocity_);
		void setGravity(float gravity_);
		void setTexture() {};

		Transform transform;

	private:
		//Render Data
		unsigned int m_VAO, m_VBO;

		//Play
		bool isPlaying = true;

		//Particle variables
		int m_particleAmount	= 0;
		float m_lifetime		= 0.0f;
		float m_elapsedtime		= 0.0f;
		float m_gravity			= -9.8f;
		bool m_looping			= true;
		glm::vec3 m_vel			= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_colour		= glm::vec3(1.0f, 0.0f, 0.0f);

		//Container of particles
		std::vector<Particle> m_particles;

		//Stopwatch
		Stopwatch* m_timer;
	};

}

#endif