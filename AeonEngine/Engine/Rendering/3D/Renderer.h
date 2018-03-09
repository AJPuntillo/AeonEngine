#ifndef RENDERER_H
#define RENDERER_H

//***
//Renderer Class:
//The renderer class takes in specified shaders and meshes and renders them.
//Contains the view and projection matrix.
//***

#include <glm/glm.hpp>

#include "../../Core/Window.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/Shader.h"
#include "Entity.h"
#include "Light.h"
#include "Skybox.h"
#include "Framebuffer.h"
#include "GameObject.h"
//Resource Managers
#include "../../DataStructures/ShaderManager.h"
#include "../../DataStructures/ModelManager.h"
#include "../../DataStructures/MaterialManager.h"

#include <vector>

namespace AEON_ENGINE {
	
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void render(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<GameObject*> objects_, std::vector<Light*> lights_);

		//void render(Camera* camera_, ShaderManager::HandleType shaderHandle_, Board* board_, std::vector<Light*> lights_);
		//void render(Camera* camera_, ShaderManager::HandleType shaderHandle_, Tile* tile_, std::vector<Light*> lights_);
		//void render(Camera* camera_, ShaderManager::HandleType shaderHandle_, Piece* piece_, std::vector<Light*> lights_);

		void render(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<GameObject*> objects_);
		void renderLightMeshes(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<Light*> lights_);
		void renderSkybox(Camera* camera_, Skybox* skybox_);
		void renderFramebuffer(ShaderManager::HandleType shaderHandle_, Framebuffer* framebuffer_);

		//Pre-Render; Must be before render is called
		void clearBuffers(glm::vec4 clearColour = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); //Optional clearColour

		//Post-Render; Must be after render is called
		void swapBuffers(Window* window_);

	private:
		std::vector<Light*> m_pointList;
		std::vector<Light*> m_directionalList;
		unsigned int lightListSize = 0;
	};

}

#endif