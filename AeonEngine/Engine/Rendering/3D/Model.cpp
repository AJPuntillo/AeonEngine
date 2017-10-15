#include "Model.h"

using namespace AEON_ENGINE;

Model::Model(const glm::vec3 pos_)
{
	m_pos = pos_;
	translate(m_pos);
}

Model::~Model()
{
	//Empty
}

void Model::rotate(const float angle_, const glm::vec3& vec_)
{
	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle_, vec_);
}

void Model::translate(const glm::vec3& vec_)
{
	m_translateMatrix = glm::translate(m_translateMatrix, vec_);
	m_pos += vec_;
}

void Model::scale(const glm::vec3& vec_)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, vec_);
}

bool Model::loadMesh()
{
	m_meshes.push_back(new Mesh());
	return true;
}

void Model::update(const float deltaTime)
{
	//Empty
}

void Model::render(Shader* shader_)
{
	//Set the Model matrix	
	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
	shader_->setMat4("model", m_modelMatrix);

	for (Mesh* mesh : m_meshes) {
		mesh->render();
	}

	//Currently the rotation and scale matrices are being reset and redrawn to prevent additive adjustents
	//Not sure if this is extremely inefficient, will have to revisit
	m_rotationMatrix = glm::mat4();
	m_scaleMatrix = glm::mat4();
}