#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

#include "../../Graphics/Shader.h"

namespace AEON_ENGINE {

	class Entity
	{
	public:

		Entity() {};
		virtual ~Entity() {};

		virtual void update(const float deltaTime) = 0;
		virtual void render(Shader* shader_) = 0;
	};

}

#endif