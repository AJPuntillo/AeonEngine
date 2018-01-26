#ifndef MESH_H
#define MESH_H

#include <GL/glew.h> //Holds all OpenGL type declarations
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Graphics/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace AEON_ENGINE {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	struct Texture {
		unsigned int id;
		std::string type;
		aiString path;
	};

	class Mesh
	{
	public:
		//Primitive type enum
		enum PrimitiveType { CUBE, PLANE };

		Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_); //For loading mesh files through Assimp
		Mesh(PrimitiveType primitiveType_); //For loading primitive meshes (Cube or Plane)
		~Mesh();

		//Render the mesh
		void render(Shader* shader_);

		//Getters
		unsigned int getVAO() { return m_VAO; }
		std::vector<Vertex> getVertices() { return vertices; }

	private:
		//Render data
		unsigned int m_VAO, m_VBO, m_EBO;

		//Mesh data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		//Initializes all the buffer objects/arrays
		void generateBuffers();

		//Check what type of mesh should be loaded
		bool m_isPrimitive = false;
	};

}

#endif