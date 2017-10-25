#include "PrimitiveMesh.h"

using namespace AEON_ENGINE;

PrimitiveMesh::PrimitiveMesh()
{
	PrimitiveVertex v;

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);

	hasIndices = false;
	generateBuffers();
}

PrimitiveMesh::PrimitiveMesh(std::vector<PrimitiveVertex> vertices_, std::vector<unsigned int> indices_)
{
	vertices = vertices_;
	indices = indices_;

	hasIndices = true;
	generateBuffers();
}

PrimitiveMesh::~PrimitiveMesh() {

	//Delete the VAO/VBO/EBO from the GPU and clear their data
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);

	if (hasIndices)
		glDeleteBuffers(1, &m_EBO);
}

void PrimitiveMesh::render()
{
	//Draw mesh
	glBindVertexArray(m_VAO);

	if (hasIndices)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}

void PrimitiveMesh::generateBuffers()
{
	//Generate buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	//Bind the VAO
	glBindVertexArray(m_VAO);

	//Bind and populate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PrimitiveVertex), &vertices[0], GL_STATIC_DRAW);

	//Bind and populate the EBO
	if (hasIndices) {
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)0); //(index of vert attrib, num of components [ex: if the attribute is a vec3, then we specify 3], type, normalize, stride -- the total size of all the attributes per vertex[offset per vertex][ex: we have 2 vec3s for each vertex, pos and col, that is a total of 6 floats], offset in the array where each attribute begins)
	glEnableVertexAttribArray(0);

	//Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)offsetof(PrimitiveVertex, normal));
	glEnableVertexAttribArray(1);

	//Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)offsetof(PrimitiveVertex, texCoords));
	glEnableVertexAttribArray(2);

	//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}