#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

#include <string>
#include <iostream>

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

}

#endif