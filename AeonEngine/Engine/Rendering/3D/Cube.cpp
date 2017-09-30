#include "Cube.h"

using namespace AEON_ENGINE;

Cube::Cube()
{
	//Set up the cube's vertex properties for the VAO/VBO/EBO

	//Vertices ---
	Vertex v;
	std::vector<Vertex> v_list;

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v_list.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v_list.push_back(v);
	//---

	//Indices ---
	unsigned int index;
	std::vector<unsigned int> i_list;

	//m_mesh = new Mesh(v_list);
}

Cube::~Cube()
{

}

void Cube::render(AEON_ENGINE::Shader* shader_)
{
	m_mesh->render(shader_, calculateModel());
}


void Cube::setPosition(glm::vec3 position_)
{
	m_position = position_;
}

void Cube::setRotation(glm::vec3 rotation_)
{
	m_rotation = rotation_;
}

void Cube::setAngle(float angle_)
{
	m_angle = angle_;
}

void Cube::setScale(glm::vec3 scale_)
{
	m_scale = scale_;
}

glm::mat4 Cube::calculateModel()
{
	glm::mat4 modelMatrix;

	modelMatrix = glm::translate(modelMatrix, m_position);
	modelMatrix = glm::rotate(modelMatrix, m_angle, m_rotation);
	modelMatrix = glm::scale(modelMatrix, m_scale);

	return modelMatrix;
}