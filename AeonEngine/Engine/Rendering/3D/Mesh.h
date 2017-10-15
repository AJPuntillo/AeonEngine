#ifndef MESH_H
#define MESH_H

#include <GL/glew.h> //Holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Graphics/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace AEON_ENGINE {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		Mesh(); //Default loads basic cube vertices
		Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_);
		~Mesh();

		void render();

		//Mesh Data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

	private:
		void generateBuffers();

		//Render data
		unsigned int m_VBO, m_VAO, m_EBO;
		bool hasIndices = false;
	};

}

#endif