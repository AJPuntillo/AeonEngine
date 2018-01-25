#ifndef SKYBOX_H
#define SKYBOX_H

//***
//Skybox Class:
//The skybox class is a specific entity used to render a cubemap/skybox.
//Inherits from Entity and needs a SkyboxMesh
//***

#include <glm/glm.hpp>

#include "Entity.h"
#include "SkyboxMesh.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/stb_image.h"
#include "../../DataStructures/ShaderManager.h"

#include <vector>

namespace AEON_ENGINE {

	class Skybox : public Entity
	{
	public:
		Skybox(std::vector<std::string> faces_, ShaderManager::HandleType shaderHandle_);
		virtual ~Skybox();

		void update(const float deltaTime) override {}
		void render(Shader* shader_) override;

		bool loadMesh();
		void loadSkybox(std::vector<std::string> faces_);

		//Getters
		Shader* getAttachedShader() const {
			Shader* temp = ShaderManager::getInstance()->getShader(m_shader);
			return temp;
		}

	private:
		SkyboxMesh* m_mesh;
		unsigned int textureID;
		ShaderManager::HandleType m_shader;
	};

}

#endif