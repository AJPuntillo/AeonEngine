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

#include <vector>

namespace AEON_ENGINE {
	
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void render(Camera* camera_, Window* window_, Shader* shader_, std::vector<Entity*> models_, std::vector<Light*> lights_);
		void render(Camera* camera_, Window* window_, Shader* shader_, std::vector<Entity*> models_); //Overload for no lights
		void render(Camera* camera_, Window* window_, Shader* shader_, Entity* skybox_); //Overload for skybox

		//Pre-Render; Must be before render is called
		void clearBuffers(glm::vec4 clearColour = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); //Optional clearColour

		//Post-Render; Must be after render is called
		void swapBuffers(Window* window_);
	};

}

#endif