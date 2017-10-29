#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
#include "PrimitiveMesh.h"
#include "../../Camera/Camera.h"

//***
//Only has hardcoded values in for the light settings. Will need to add functionality later.
//***

namespace AEON_ENGINE {

	class Light : public Entity
	{
	public:
		enum LightType { NONE, DIRECTIONAL, POINT };

		Light(LightType type_, const glm::vec3 pos_, bool hasMesh = false);
		virtual ~Light();

		//Matrix manipulation
		void rotate(const float angle_, const glm::vec3& vec_) override;
		void translate(const glm::vec3& vec_) override;
		void scale(const glm::vec3& vec_) override;

		//Updating and rendering
		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		//Mesh
		void loadMesh();

		//Getters
		LightType getLightType() { return m_lightType; }
		glm::vec3 getPos() { return m_pos; }
		glm::vec3 getDirection() { return m_direction; }
		glm::vec3 getAmbient() { return m_ambient; }
		glm::vec3 getDiffuse() { return m_diffuse; }
		glm::vec3 getSpecular() { return m_specular; }
		float getShininess() { return m_shininess; }
		float getConstant() { return m_constant; }
		float getLinear() { return m_linear; }
		float getQuadratic() { return m_quadratic; }

		//Setters
		void setLightType(LightType type_);

	private:
		//Light settings				//Defaults
		glm::vec3 m_ambient				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_diffuse				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_specular			= glm::vec3(0.0f, 0.0f, 0.0f);
		float m_shininess				= 64;
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
		//Has a mesh?
		bool m_hasMesh					= false;
		//Mesh
		PrimitiveMesh* m_mesh;
	};

}

#endif