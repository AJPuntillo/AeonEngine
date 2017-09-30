#ifndef CUBE_H
#define CUBE_H

#include "PrimitiveMesh.h"

namespace AEON_ENGINE {

	class Cube
	{
	public:
		Cube();
		~Cube();

		void render(AEON_ENGINE::Shader* shader_);

		//Setters
		void setPosition(glm::vec3 position_);
		void setRotation(glm::vec3 rotation_);
		void setAngle(float angle_);
		void setScale(glm::vec3 scale_);

		//Getters
		glm::vec3 getPosition() const { return m_position; };
		glm::vec3 getRotation() const { return m_rotation; };
		float getAngle() const { return m_angle; };
		glm::vec3 getScale() const { return m_scale; };


	private:
		//Calculate the changes made to the model in the model matrix (Rule of thumb is always: Translate -> Rotate -> Scale)
		glm::mat4 calculateModel();

		//Cube mesh
		PrimitiveMesh* m_mesh;

		//Cube values		 //Defaults
		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_angle = 0.0f;
		glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	};

}

#endif