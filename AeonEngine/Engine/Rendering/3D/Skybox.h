#ifndef SKYBOX_H
#define SKYBOX_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "SkyboxMesh.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"

#include <vector>

namespace AEON_ENGINE {

	class Skybox : public Entity
	{
	public:
		Skybox(std::vector<std::string> faces_);
		virtual ~Skybox();

		void rotate(const float angle_, const glm::vec3& vec_) {}
		void translate(const glm::vec3& vec_) {}
		void scale(const glm::vec3& vec_) {}

		void update(const float deltaTime) {}
		void render(Shader* shader_) override;

		bool loadMesh();
		void loadSkybox(std::vector<std::string> faces_);

	private:
		SkyboxMesh* m_mesh;
		unsigned int textureID;
	};

}

#endif