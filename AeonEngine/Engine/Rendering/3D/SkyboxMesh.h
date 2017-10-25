#ifndef SKYBOXMESH_H
#define SKYBOXMESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Graphics/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace AEON_ENGINE {

	struct SkyboxVertex
	{
		glm::vec3 position;
	};

	class SkyboxMesh
	{
	public:
		SkyboxMesh(); //Default loads basic cube vertices
		~SkyboxMesh();

		void render();

		//SkyboxVertex Data
		std::vector<SkyboxVertex> vertices;

	private:
		void generateBuffers();

		//Render data
		unsigned int m_VBO, m_VAO;
	};

}

#endif