#ifndef RENDERER_H
#define RENDERER_H

#include "../../Graphics/Shader.h"

namespace AEON_ENGINE {
	
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		//Getters
		Shader* getShader() const { return m_shader; }

	private:
		//Shader program
		Shader* m_shader = nullptr;
	};

}

#endif