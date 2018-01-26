#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
#include "Mesh.h"
#include "Transform.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"
#include "../../DataStructures/ShaderManager.h"

//***
//Only has hardcoded values in for the light settings. Will need to add functionality later.
//***

namespace AEON_ENGINE {

	class Light : public Entity
	{
	//Light type defines (Might want to change to enum later)
	#define LIGHT_DIRECTIONAL 0
	#define LIGHT_POINT 1

	public:
		Light(unsigned int type_, bool hasMesh = false);
		virtual ~Light();

		//Updating and rendering
		void update(const float deltaTime) override;
		void render(Shader* shader_) override;

		//Mesh
		void loadMesh();

		//Getters
		unsigned int getLightType() { return m_lightType; }
		glm::vec3 getDirection() { return m_direction; }
		glm::vec3 getAmbient() { return m_ambient; }
		glm::vec3 getDiffuse() { return m_diffuse; }
		glm::vec3 getSpecular() { return m_specular; }
		float getShininess() { return m_shininess; }
		float getConstant() { return m_constant; }
		float getLinear() { return m_linear; }
		float getQuadratic() { return m_quadratic; }

		//Setters
		void setLightType(unsigned int type_);
		void setDirection(glm::vec3 direction_);
		void setLightIntensity(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);
		void setAttenuation(float constant_, float linear_, float quadratic_);
		void setShininess(float shininess_);

		//Transform
		Transform transform;

	private:
		//Light intensity				//Defaults
		glm::vec3 m_ambient				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_diffuse				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_specular			= glm::vec3(0.0f, 0.0f, 0.0f);
		float m_shininess				= 64.0f;
		//Light attenuation
		float m_constant				= 0.0f;
		float m_linear					= 0.0f;
		float m_quadratic				= 0.0f;
		//Light direction
		glm::vec3 m_direction			= glm::vec3(0.0f, 0.0f, 0.0f);
		//Cutoff and falloff
		float m_cutOff					= 0.0f;
		float m_outerCutOff				= 0.0f;
		//Light type
		unsigned int m_lightType		= LIGHT_POINT;
		//Has a mesh?
		bool m_hasMesh					= false;
		//Mesh
		Mesh* m_mesh;
	};

}

#endif