#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

//***
//Framebuffer Class:
//The framebuffer class is responsible creating a plane and rendering the scene to that specific plane
//This is useful for post-processing effects, multiple screens, mirror effects.
//Inherits from Entity.
//***

#include <glm/glm.hpp>

#include "Entity.h"
#include "PrimitiveMesh.h"
#include "../../Camera/Camera.h"
#include "../../Core/Window.h"

#include <vector>

namespace AEON_ENGINE {

	class Framebuffer : public Entity
	{
	public:
		Framebuffer(Window* window_);
		virtual ~Framebuffer();

		void update(const float deltaTime) override {}
		void render(Shader* shader_) override;

		void setFramebuffer(Window* window_);
		bool loadMesh();

		void updateFramebufferSize(Window* window_); //Checks to see if thw windowsize has changed, if so then adjust the framebuffer

		void bindBuffer();
		void unbindBuffer();

	private:
		PrimitiveMesh* m_mesh;
		unsigned int m_framebuffer;
		unsigned int m_texColourBuffer;
		unsigned int m_screenWidth;
		unsigned int m_screenHeight;
	};

}

#endif