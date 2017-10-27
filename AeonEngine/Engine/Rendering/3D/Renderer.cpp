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

void Renderer::render(Camera* camera_, Window* window_, Shader* shader_, std::vector<Entity*> models_) //Change to take in a vector of models/entity
{
	//Rendering
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_->use();

	//Set view and projection matrix of the world
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProj());

	//Set view position for lighting
	shader_->setVec3("viewPos", camera_->getPos());


	for (Entity* entity : models_) {
		entity->render(shader_);
	}

	//window_->swapBuffers();
}

void Renderer::render(Camera* camera_, Window* window_, Shader* shader_, Entity* skybox_)
{
	shader_->use();

	//Set view and projection matrix of the world
	//Convert the view matrix to a 3x3 to remove translation
	glm::mat4 skyboxView = glm::mat4(glm::mat3(camera_->getView()));
	shader_->setMat4("view", skyboxView);
	shader_->setMat4("projection", camera_->getProj());

	skybox_->render(shader_);
}