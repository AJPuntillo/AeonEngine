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

void Renderer::render(Camera* camera_, Window* window_, Shader* shader_, std::vector<Entity*> models_, std::vector<Light*> lights_)
{
	shader_->use();

	//Set view and projection matrix of the world
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProj());

	//***Temporarily disabled until advanced lgihting is explored
	////Current bug that blends the different lights together to strongly
	////Lighting
	////Set view position for lighting
	//shader_->setVec3("viewPos", camera_->getPos());
	////Set the number of point lights in the scene
	//shader_->setInt("NumOfLights", lights_.size());
	////Loop through all the lights in the list and set their uniforms based on the Light Type
	//for (int i = 0; i < lights_.size(); i++) {
	//	switch (lights_[i]->getLightType()) {
	//	case Light::LightType::DIRECTIONAL:
	//		shader_->setVec3("dirLight.direction", lights_[i]->getDirection());
	//		shader_->setVec3("dirLight.ambient", lights_[i]->getAmbient());
	//		shader_->setVec3("dirLight.diffuse", lights_[i]->getDiffuse());
	//		shader_->setVec3("dirLight.specular", lights_[i]->getSpecular());
	//		shader_->setFloat("shininess", lights_[i]->getShininess());
	//		break;

	//	case Light::LightType::POINT:
	//		shader_->setVec3("pointLights[" + std::to_string(i) + "].position", lights_[i]->getPos());
	//		shader_->setVec3("pointLights[" + std::to_string(i) + "].ambient", lights_[i]->getAmbient());
	//		shader_->setVec3("pointLights[" + std::to_string(i) + "].diffuse", lights_[i]->getDiffuse());
	//		shader_->setVec3("pointLights[" + std::to_string(i) + "].specular", lights_[i]->getSpecular());
	//		shader_->setFloat("pointLights[" + std::to_string(i) + "].constant", lights_[i]->getConstant());
	//		shader_->setFloat("pointLights[" + std::to_string(i) + "].linear", lights_[i]->getLinear());
	//		shader_->setFloat("pointLights[" + std::to_string(i) + "].quadratic", lights_[i]->getQuadratic());
	//		shader_->setFloat("shininess", lights_[i]->getShininess());
	//		break;
	//	}
	//}
	
	//Temporary lighting; setting the direcitonal light
	shader_->setVec3("dirLight.direction", lights_[0]->getDirection());
	shader_->setVec3("dirLight.ambient", lights_[0]->getAmbient());
	shader_->setVec3("dirLight.diffuse", lights_[0]->getDiffuse());
	shader_->setVec3("dirLight.specular", lights_[0]->getSpecular());
	shader_->setFloat("shininess", lights_[0]->getShininess());

	for (Entity* entity : models_) {
		entity->render(shader_);
	}

	for (Light* light : lights_) {
		light->render(shader_);
	}
}

void Renderer::render(Camera* camera_, Window* window_, Shader* shader_, std::vector<Entity*> models_) //Change to take in a vector of models/entity
{
	shader_->use();

	//Set view and projection matrix of the world
	shader_->setMat4("view", camera_->getView());
	shader_->setMat4("projection", camera_->getProj());

	//Set view position for lighting
	shader_->setVec3("viewPos", camera_->getPos());

	for (Entity* entity : models_) {
		entity->render(shader_);
	}
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

void Renderer::clearBuffers(glm::vec4 clearColour_)
{
	glClearColor(clearColour_.x, clearColour_.y, clearColour_.z, clearColour_.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers(Window* window_)
{
	window_->swapBuffers();
}