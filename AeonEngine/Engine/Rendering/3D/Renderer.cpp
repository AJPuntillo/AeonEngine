#include "Renderer.h"

using namespace AEON_ENGINE;

Renderer::Renderer()
{
	//Empty
}

Renderer::~Renderer()
{
	//Delete Shader
	delete m_shader;
	m_shader = nullptr;
}