#include "PrimitiveMesh.h"

using namespace AEON_ENGINE;

PrimitiveMesh::PrimitiveMesh(std::vector<Vertex> vertices_) {

	vertices = vertices_;

	generateBuffers();
}

PrimitiveMesh::~PrimitiveMesh() {

	//Delete the VAO/VBO/EBO from the GPU and clear their data
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}


void PrimitiveMesh::generateBuffers() {

	//Generate buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	//Bind the VAO
	glBindVertexArray(m_VAO);

	//Bind and populate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//Bind and populate the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //(index of vert attrib, num of components [ex: if the attribute is a vec3, then we specify 3], type, normalize, stride -- the total size of all the attributes per vertex[offset per vertex][ex: we have 2 vec3s for each vertex, pos and col, that is a total of 6 floats], offset in the array where each attribute begins)
	glEnableVertexAttribArray(0);

	//Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}


void PrimitiveMesh::render(Shader* shader_, glm::mat4 modelMatrix_) {

	shader_->setMat4("model", modelMatrix_);

	//Draw mesh
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);

	//Always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}