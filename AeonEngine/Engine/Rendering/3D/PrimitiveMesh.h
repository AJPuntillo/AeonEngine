#ifndef PRIMITIVEMESH_H
#define PRIMITIVEMESH_H

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

	struct PrimitiveVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

	};

	class PrimitiveMesh
	{
	//Primitive type defines (Might want to change to enum later)
	#define PRIM_TYPE_CUBE 0
	#define PRIM_TYPE_PLANE 1

	public:
		PrimitiveMesh(const int primitiveType_); //Default loads basic cube vertices
		PrimitiveMesh(std::vector<PrimitiveVertex> vertices_, std::vector<unsigned int> indices_);
		~PrimitiveMesh();
		std::vector<PrimitiveVertex>* getVerticies();

		void render();

		//PrimitiveMesh Data
		std::vector<PrimitiveVertex> vertices;
		std::vector<unsigned int> indices;

	private:
		void generateBuffers();

		//Render data
		unsigned int m_VBO, m_VAO, m_EBO;
		bool hasIndices = false;
	};

}

#endif