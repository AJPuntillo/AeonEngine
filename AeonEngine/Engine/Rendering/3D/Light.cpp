#include "Light.h"

using namespace AEON_ENGINE;

Light::Light(unsigned int type_, const glm::vec3 pos_, bool hasMesh)
{
	setLightType(type_);
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
	if (m_hasMesh) {
		delete m_mesh;
		m_mesh = nullptr;
	}
}

void Light::setLightType(unsigned int type_)
{
	m_lightType = type_;

	switch (type_) {
	case LIGHT_DIRECTIONAL:
		m_lightType = LIGHT_DIRECTIONAL;
		m_ambient = glm::vec3(0.6f, 0.6f, 0.6f);
		m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		m_specular = glm::vec3(0.6f, 0.6f, 0.6f);
		m_shininess = 32.0f;
		m_direction = glm::vec3(-0.2f, -0.3f, -0.1f);
		//Reset unused values
		m_cutOff = 0.0f;
		m_outerCutOff = 0.0f;
		m_constant = 0.0f;
		m_linear = 0.0f;
		m_quadratic = 0.0f;
		break;

	case LIGHT_POINT:
		m_lightType = LIGHT_POINT;
		m_ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
		m_shininess = 32.0f;
		m_constant = 1.0f;
		m_linear = 0.09f;
		m_quadratic = 0.032;
		//Reset unused values
		m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cutOff = 0.0f;
		m_outerCutOff = 0.0f;
		break;
	}
}

void Light::setDirection(glm::vec3 direction_)
{
	//Warning displayed if the method is used with the wrong light type
	if (m_lightType == LIGHT_POINT)
		std::cout << "WARNING::LIGHT TYPE DOES NOT UTILIZE DIRECTION VALUE::LIGHT WILL BE UNAFFECTED" << std::endl;

	m_direction = direction_;
}

void Light::setLightIntensity(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_)
{
	m_ambient = ambient_;
	m_diffuse = diffuse_;
	m_specular = specular_;
}

void Light::setAttenuation(float constant_, float linear_, float quadratic_)
{
	//Warning displayed if the method is used with the wrong light type
	if (m_lightType == LIGHT_DIRECTIONAL)
		std::cout << "WARNING::LIGHT TYPE DOES NOT UTILIZE ATTENUATION VALUES::LIGHT WILL BE UNAFFECTED" << std::endl;

	m_constant = constant_;
	m_linear = linear_;
	m_quadratic = quadratic_;
}

void Light::setShininess(float shininess_)
{
	m_shininess = shininess_;
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

	if (m_hasMesh) {

		//Set texture (if there is one)
		//if (&texture_diffuse != nullptr) {
		//	shader_->setInt("texture_diffuse1", 0);
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, texture_diffuse);
		//}

		//if (&texture_specular != nullptr) {
		//	shader_->setInt("texture_specular1", 1);
		//	glActiveTexture(GL_TEXTURE1);
		//	glBindTexture(GL_TEXTURE_2D, texture_specular);
		//}

		m_mesh->render();
	}

	//Currently the rotation and scale matrices are being reset and redrawn to prevent additive adjustents
	//Not sure if this is extremely inefficient, will have to revisit
	//m_rotationMatrix = glm::mat4();
	//m_scaleMatrix = glm::mat4();
}

void Light::loadMesh()
{
	m_mesh = new PrimitiveMesh(PRIM_TYPE_CUBE);
}