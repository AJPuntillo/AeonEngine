#include "Mesh.h"

using namespace AEON_ENGINE;

Mesh::Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_)
{
	this->vertices = vertices_;
	this->indices = indices_;
	this->textures = textures_;

	//Hardcode a colour for every vertex -- FOR TESTING
	/*for (int i = 0; i < vertices.size(); i++)
		this->vertices[i].colour = glm::vec3(1.0f, 0.0f, 0.0f);*/

	generateBuffers();
}

//Mesh::~Mesh()
//{
//	//Delete the VAO/VBO/EBO from the GPU and clear their data
//	glDeleteVertexArrays(1, &m_VAO);
//	glDeleteBuffers(1, &m_VBO);
//	glDeleteBuffers(1, &m_EBO);
//}

void Mesh::render(Shader* shader_)
{
	//Bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); //Active proper texture unit before binding
										  //Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // transfer unsigned int to stream
		else if (name == "texture_specular")
			ss << specularNr++; // transfer unsigned int to stream
		else if (name == "texture_normal")
			ss << normalNr++; // transfer unsigned int to stream
		else if (name == "texture_height")
			ss << heightNr++; // transfer unsigned int to stream
		number = ss.str();
		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader_->getShaderProgram(), (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//Render mesh
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//Always good practice to set everything back to defaults once configured
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::generateBuffers()
{
	//Create buffers/arrays
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Set the vertex attribute pointers
	//Positions attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	//TextureCoords attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	//Tangent attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	//Bitangent attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	glBindVertexArray(0);
}