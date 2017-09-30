#ifndef PRIMITIVEMESH_H
#define PRIMITIVEMESH_H

#include <GL/glew.h> //Holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Graphics/Shader.h"
#include "Vertex.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


namespace AEON_ENGINE {

	class PrimitiveMesh {

	public:
		PrimitiveMesh(std::vector<Vertex> vertices_);
		~PrimitiveMesh();

		void render(Shader* shader_, glm::mat4 modelMatrix_);

		//Mesh Data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

	private:
		void generateBuffers();

		//Render data
		unsigned int m_VBO, m_VAO, m_EBO;
	};
}

#endif