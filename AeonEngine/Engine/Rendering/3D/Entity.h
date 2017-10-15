#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

namespace AEON_ENGINE {

	class Entity
	{
	protected:
		//Maybe pointers? Not sure if it will help optimization
		glm::mat4 m_modelMatrix;
		glm::mat4 m_translateMatrix;
		glm::mat4 m_rotationMatrix;
		glm::mat4 m_scaleMatrix;

		glm::vec3 m_pos;

	public:

		Entity() {};
		virtual ~Entity() {};

		virtual void rotate(const float angle_, const glm::vec3& vec_) = 0;
		virtual void translate(const glm::vec3& vec_) = 0;
		virtual void scale(const glm::vec3& vec_) = 0;
	};

}

#endif