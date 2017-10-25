#include "SkyboxMesh.h"

using namespace AEON_ENGINE;

SkyboxMesh::SkyboxMesh()
{
	SkyboxVertex v;

	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	vertices.push_back(v);

	generateBuffers();
}

SkyboxMesh::~SkyboxMesh() {

	//Delete the VAO/VBO/EBO from the GPU and clear their data
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void SkyboxMesh::render()
{
	//Draw mesh
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void SkyboxMesh::generateBuffers()
{
	//Generate buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	//Bind the VAO
	glBindVertexArray(m_VAO);

	//Bind and populate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SkyboxVertex), &vertices[0], GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SkyboxVertex), (void*)0); //(index of vert attrib, num of components [ex: if the attribute is a vec3, then we specify 3], type, normalize, stride -- the total size of all the attributes per vertex[offset per vertex][ex: we have 2 vec3s for each vertex, pos and col, that is a total of 6 floats], offset in the array where each attribute begins)
	glEnableVertexAttribArray(0);

	//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}