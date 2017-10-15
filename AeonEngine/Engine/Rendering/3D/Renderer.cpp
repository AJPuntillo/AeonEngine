#include "Renderer.h"

using namespace AEON_ENGINE;

Renderer::Renderer()
{
	//Empty
}

Renderer::~Renderer()
{
	//Empty
}

void Renderer::render(Camera* camera_, Window* window_, Shader* shader_, Model* model_) //Change to take in a vector of models
{
	//Rendering
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view and projection matrix of the world
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProj());

	shader_->use();
	model_->render(shader_);

	window_->swapBuffers();
}