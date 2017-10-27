#include "Light.h"

using namespace AEON_ENGINE;

Light::Light(LightType type_, const glm::vec3 pos_, bool hasMesh)
{
	//setLightType(type_);
	translate(pos_);
	m_hasMesh = hasMesh;

	if (m_hasMesh) {
		loadMesh();
		//For the size of the Mesh
		scale(glm::vec3(0.25f, 0.25f, 0.25f));
	}

}

Light::~Light()
{
	delete m_mesh;
	m_mesh = nullptr;
}

void Light::setLightType(LightType type_)
{
	m_lightType = type_;

	switch (type_) {
	case NONE:
		m_lightType = NONE;
		m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		m_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
		m_specular = glm::vec3(0.0f, 0.0f, 0.0f);
		m_constant = 0.0f;
		m_linear = 0.0f;
		m_quadratic = 0.0f;
		m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cutOff = 0.0f;
		m_outerCutOff = 0.0f;
		break;

	case DIRECTIONAL:
		m_lightType = DIRECTIONAL;
		m_ambient = glm::vec3(0.6f, 0.6f, 0.6f);
		m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		m_specular = glm::vec3(0.6f, 0.6f, 0.6f);
		m_direction = glm::vec3(-0.2f, -0.3f, -0.1f);
		//Reset unused values
		m_cutOff = 0.0f;
		m_outerCutOff = 0.0f;
		m_constant = 0.0f;
		m_linear = 0.0f;
		m_quadratic = 0.0f;
		break;

	case POINT:
		m_lightType = POINT;
		m_ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
		m_constant = 1.0f;
		m_linear = 0.09;
		m_quadratic = 0.032;
		//Reset unused values
		m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cutOff = 0.0f;
		m_outerCutOff = 0.0f;
		break;
	}
}

void Light::rotate(const float angle_, const glm::vec3& vec_)
{
	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle_, vec_);
}

void Light::translate(const glm::vec3& vec_)
{
	m_translateMatrix = glm::translate(m_translateMatrix, vec_);
	m_pos += vec_;
}

void Light::scale(const glm::vec3& vec_)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, vec_);
}

void Light::update(const float deltaTime)
{
	//Empty
}

void Light::render(Shader* shader_)
{
	//Set the Model matrix	
	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
	shader_->setMat4("model", m_modelMatrix);

	//**FIX THIS LATER**//
	shader_->setVec3("light.position", m_pos);

	//Light properties
	shader_->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader_->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader_->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	//Material properties
	shader_->setFloat("shininess", 64.0f);

	if (m_hasMesh)
		m_mesh->render();

	//Currently the rotation and scale matrices are being reset and redrawn to prevent additive adjustents
	//Not sure if this is extremely inefficient, will have to revisit
	//m_rotationMatrix = glm::mat4();
	//m_scaleMatrix = glm::mat4();
}

void Light::loadMesh()
{
	m_mesh = new PrimitiveMesh();
}