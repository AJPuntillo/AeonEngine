#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace AEON_ENGINE {

	class Transform
	{
	public:
		Transform();
		~Transform();

		void updateModelMatrix();

		void translateBy	(float x_, float y_, float z_);
		void translateBy	(glm::vec3 pos_);

		void rotateBy		(float angle_, float x_, float y_, float z_);
		void rotateBy		(glm::vec4 rot_);

		void scaleBy		(float x_, float y_, float z_);
		void scaleBy		(glm::vec3 scale_);

		void setPosition	(float x_, float y_, float z_);
		void setPosition	(glm::vec3 pos_);

		glm::mat4 modelMatrix	= glm::mat4();
		glm::vec3 position		= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation		= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale			= glm::vec3(0.0f, 0.0f, 0.0f);

	private:
		glm::mat4 translationMatrix		= glm::mat4();
		glm::mat4 rotationMatrix		= glm::mat4();
		glm::mat4 scaleMatrix			= glm::mat4();

		//Bool to check if the modelmatrix should be updated (Small optimization)
		bool transformHasChanged		= true;
	};

}

#endif