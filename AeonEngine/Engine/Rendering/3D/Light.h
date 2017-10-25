#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
#include "../../Camera/Camera.h"

//***
//Only has hardcoded values in for the light settings. Will need to add functionality later.
//***

namespace AEON_ENGINE {

	class Light : public Entity
	{
	public:
		enum LightType { NONE, DIRECTIONAL, POINT, SPOT };

		Light(LightType type_, const glm::vec3 pos_);
		virtual ~Light();

		//Matrix manipulation
		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		//Updating and rendering
		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		//Getters
		LightType getLightType() { return m_lightType; }

		//Setters
		void setLightType(LightType type_);

	private:
		//Light settings				//Defaults
		glm::vec3 m_ambient				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_diffuse				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_specular			= glm::vec3(0.0f, 0.0f, 0.0f);
		//Light intensity
		float m_constant				= 0.0f;
		float m_linear					= 0.0f;
		float m_quadratic				= 0.0f;
		//Light direction
		glm::vec3 m_direction			= glm::vec3(0.0f, 0.0f, 0.0f);
		//Cutoff and falloff
		float m_cutOff					= 0.0f;
		float m_outerCutOff				= 0.0f;
		//Light type
		LightType m_lightType			= NONE;
	};

}

#endif