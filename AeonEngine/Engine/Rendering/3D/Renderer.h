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
#include "Model.h"

namespace AEON_ENGINE {
	
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void render(Camera* camera_, Window* window_, Shader* shader_, Model* model_);
	};

}

#endif