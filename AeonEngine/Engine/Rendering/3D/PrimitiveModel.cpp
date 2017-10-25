#include "PrimitiveModel.h"

using namespace AEON_ENGINE;

PrimitiveModel::PrimitiveModel()
{
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	translate(m_pos);
	loadMesh();
}

PrimitiveModel::PrimitiveModel(const glm::vec3 pos_, char const *path)
{
	m_pos = pos_;
	translate(m_pos);
	loadMesh();
	loadTexture(path);
}

PrimitiveModel::PrimitiveModel(const glm::vec3 pos_)
{
	m_pos = pos_;
	translate(m_pos);
	loadMesh();
}

PrimitiveModel::PrimitiveModel(char const *path)
{
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	translate(m_pos);
	loadMesh();
	loadTexture(path);
}

PrimitiveModel::~PrimitiveModel()
{
	//Empty
}

void PrimitiveModel::rotate(const float angle_, const glm::vec3& vec_)
{
	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle_, vec_);
}

void PrimitiveModel::translate(const glm::vec3& vec_)
{
	m_translateMatrix = glm::translate(m_translateMatrix, vec_);
	m_pos += vec_;
}

void PrimitiveModel::scale(const glm::vec3& vec_)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, vec_);
}

void PrimitiveModel::update(const float deltaTime)
{
	//Empty
}

void PrimitiveModel::render(Shader* shader_)
{
	//Set the Model matrix	
	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
	shader_->setMat4("model", m_modelMatrix);

	//Set texture (if there is one)
	if (&textureID != nullptr) {
		shader_->setInt("texture1", 0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	for (PrimitiveMesh* mesh : m_meshes) {
		mesh->render();
	}

	//Currently the rotation and scale matrices are being reset and redrawn to prevent additive adjustents
	//Not sure if this is extremely inefficient, will have to revisit
	//***The matrices need to be reset when constantly updated
	//m_rotationMatrix = glm::mat4();
}

bool PrimitiveModel::loadMesh()
{
	m_meshes.push_back(new PrimitiveMesh());
	return true;
}

void PrimitiveModel::loadTexture(char const* path)
{
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); //Depending on the format, choose repeat or clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//stbi_set_flip_vertically_on_load(true); //Flippy

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}