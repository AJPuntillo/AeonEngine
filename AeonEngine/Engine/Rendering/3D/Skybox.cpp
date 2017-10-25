#include "Skybox.h"

using namespace AEON_ENGINE;

Skybox::Skybox(std::vector<std::string> faces_)
{
	loadMesh();
	loadSkybox(faces_);
}

Skybox::~Skybox()
{
	//Empty
}

void Skybox::render(Shader* shader_)
{
	shader_->setInt("skybox", 0);
	glDepthFunc(GL_LEQUAL); //Change depth function so depth test passes when values are equal to depth buffer's content
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	m_mesh->render();

	glDepthFunc(GL_LESS);  //Set depth function back to default
}

bool Skybox::loadMesh()
{
	m_mesh = new SkyboxMesh();

	return true;
}

void Skybox::loadSkybox(std::vector<std::string> faces_)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces_.size(); i++)
	{
		unsigned char *data = stbi_load(faces_[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces_[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}