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

void Renderer::render(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<GameObject*> objects_, std::vector<Light*> lights_)
{
	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);

	shader->use();

	//Set view and projection matrix of the world
	shader->setMat4("view", camera_->getView());
	shader->setMat4("projection", camera_->getProj());

	//Set view position for lighting
	shader->setVec3("viewPos", camera_->getPos());
	//Set the number of point lights in the scene
	shader->setInt("NumOfLights", lights_.size());

	//Check to see if the light vector has been increased/decreased in size, so that lights are constantly being pushed
	if (lightListSize != lights_.size()) {
		//Loop through all the lights and sort them in their own type-specific vector list
		//This is to prevent the lights from being in the incorrect order in the shader's vector light lists
		for (int i = 0; i < lights_.size(); i++) {
			switch (lights_[i]->getLightType()) {
			case LIGHT_DIRECTIONAL:
				m_directionalList.push_back(lights_[i]);
				break;

			case LIGHT_POINT:
				m_pointList.push_back(lights_[i]);
			}
		}

		//If the light vector has changed, update the size value for the next comparison
		lightListSize = lights_.size();
	}

	//Set the uniforms for each directional light in the vector list
	for (int i = 0; i < m_directionalList.size(); i++) {
		shader->setVec3("dirLight.direction", m_directionalList[i]->getDirection());
		shader->setVec3("dirLight.ambient", m_directionalList[i]->getAmbient());
		shader->setVec3("dirLight.diffuse", m_directionalList[i]->getDiffuse());
		shader->setVec3("dirLight.specular", m_directionalList[i]->getSpecular());
		shader->setFloat("shininess", m_directionalList[i]->getShininess());
	}

	//Set the uniforms for each point light in the vector list
	for (int i = 0; i < m_pointList.size(); i++) {
		shader->setVec3("pointLights[" + std::to_string(i) + "].position", m_pointList[i]->transform.position);
		shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", m_pointList[i]->getAmbient());
		shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", m_pointList[i]->getDiffuse());
		shader->setVec3("pointLights[" + std::to_string(i) + "].specular", m_pointList[i]->getSpecular());
		shader->setFloat("pointLights[" + std::to_string(i) + "].constant", m_pointList[i]->getConstant());
		shader->setFloat("pointLights[" + std::to_string(i) + "].linear", m_pointList[i]->getLinear());
		shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", m_pointList[i]->getQuadratic());
		shader->setFloat("shininess", m_pointList[i]->getShininess());
	}

	//Enable face culling (Default set to CCW)
	glEnable(GL_CULL_FACE);

	for (GameObject* obj : objects_) {
		obj->render(shader);
	}

	//Disable face culling (Default set to CCW)
	glDisable(GL_CULL_FACE);
}


/////////////BOARD TEST////////////
//void Renderer::render(Camera* camera_, ShaderManager::HandleType shaderHandle_, Board* board_, std::vector<Light*> lights_)
//{
//	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);
//
//	shader->use();
//
//	//Set view and projection matrix of the world
//	shader->setMat4("view", camera_->getView());
//	shader->setMat4("projection", camera_->getProj());
//
//	//Set view position for lighting
//	shader->setVec3("viewPos", camera_->getPos());
//	//Set the number of point lights in the scene
//	shader->setInt("NumOfLights", lights_.size());
//
//	//Check to see if the light vector has been increased/decreased in size, so that lights are constantly being pushed
//	if (lightListSize != lights_.size()) {
//		//Loop through all the lights and sort them in their own type-specific vector list
//		//This is to prevent the lights from being in the incorrect order in the shader's vector light lists
//		for (int i = 0; i < lights_.size(); i++) {
//			switch (lights_[i]->getLightType()) {
//			case LIGHT_DIRECTIONAL:
//				m_directionalList.push_back(lights_[i]);
//				break;
//
//			case LIGHT_POINT:
//				m_pointList.push_back(lights_[i]);
//			}
//		}
//
//		//If the light vector has changed, update the size value for the next comparison
//		lightListSize = lights_.size();
//	}
//
//	//Set the uniforms for each directional light in the vector list
//	for (int i = 0; i < m_directionalList.size(); i++) {
//		shader->setVec3("dirLight.direction", m_directionalList[i]->getDirection());
//		shader->setVec3("dirLight.ambient", m_directionalList[i]->getAmbient());
//		shader->setVec3("dirLight.diffuse", m_directionalList[i]->getDiffuse());
//		shader->setVec3("dirLight.specular", m_directionalList[i]->getSpecular());
//		shader->setFloat("shininess", m_directionalList[i]->getShininess());
//	}
//
//	//Set the uniforms for each point light in the vector list
//	for (int i = 0; i < m_pointList.size(); i++) {
//		shader->setVec3("pointLights[" + std::to_string(i) + "].position", m_pointList[i]->transform.position);
//		shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", m_pointList[i]->getAmbient());
//		shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", m_pointList[i]->getDiffuse());
//		shader->setVec3("pointLights[" + std::to_string(i) + "].specular", m_pointList[i]->getSpecular());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].constant", m_pointList[i]->getConstant());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].linear", m_pointList[i]->getLinear());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", m_pointList[i]->getQuadratic());
//		shader->setFloat("shininess", m_pointList[i]->getShininess());
//	}
//
//	//Enable face culling (Default set to CCW)
//	glEnable(GL_CULL_FACE);
//
//	board_->render(shader);
//
//	//Disable face culling (Default set to CCW)
//	glDisable(GL_CULL_FACE);
//}
//
//void Renderer::render(Camera* camera_, ShaderManager::HandleType shaderHandle_, Piece* piece_, std::vector<Light*> lights_)
//{
//	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);
//
//	shader->use();
//
//	//Set view and projection matrix of the world
//	shader->setMat4("view", camera_->getView());
//	shader->setMat4("projection", camera_->getProj());
//
//	//Set view position for lighting
//	shader->setVec3("viewPos", camera_->getPos());
//	//Set the number of point lights in the scene
//	shader->setInt("NumOfLights", lights_.size());
//
//	//Check to see if the light vector has been increased/decreased in size, so that lights are constantly being pushed
//	if (lightListSize != lights_.size()) {
//		//Loop through all the lights and sort them in their own type-specific vector list
//		//This is to prevent the lights from being in the incorrect order in the shader's vector light lists
//		for (int i = 0; i < lights_.size(); i++) {
//			switch (lights_[i]->getLightType()) {
//			case LIGHT_DIRECTIONAL:
//				m_directionalList.push_back(lights_[i]);
//				break;
//
//			case LIGHT_POINT:
//				m_pointList.push_back(lights_[i]);
//			}
//		}
//
//		//If the light vector has changed, update the size value for the next comparison
//		lightListSize = lights_.size();
//	}
//
//	//Set the uniforms for each directional light in the vector list
//	for (int i = 0; i < m_directionalList.size(); i++) {
//		shader->setVec3("dirLight.direction", m_directionalList[i]->getDirection());
//		shader->setVec3("dirLight.ambient", m_directionalList[i]->getAmbient());
//		shader->setVec3("dirLight.diffuse", m_directionalList[i]->getDiffuse());
//		shader->setVec3("dirLight.specular", m_directionalList[i]->getSpecular());
//		shader->setFloat("shininess", m_directionalList[i]->getShininess());
//	}
//
//	//Set the uniforms for each point light in the vector list
//	for (int i = 0; i < m_pointList.size(); i++) {
//		shader->setVec3("pointLights[" + std::to_string(i) + "].position", m_pointList[i]->transform.position);
//		shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", m_pointList[i]->getAmbient());
//		shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", m_pointList[i]->getDiffuse());
//		shader->setVec3("pointLights[" + std::to_string(i) + "].specular", m_pointList[i]->getSpecular());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].constant", m_pointList[i]->getConstant());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].linear", m_pointList[i]->getLinear());
//		shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", m_pointList[i]->getQuadratic());
//		shader->setFloat("shininess", m_pointList[i]->getShininess());
//	}
//
//	//Enable face culling (Default set to CCW)
//	glEnable(GL_CULL_FACE);
//
//	piece_->render(shader);
//
//	//Disable face culling (Default set to CCW)
//	glDisable(GL_CULL_FACE);
//}
//
///////////////////////////////////


void Renderer::render(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<GameObject*> objects_)
{
	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);

	//Enable face culling (Default set to CCW)
	glEnable(GL_CULL_FACE);

	for (GameObject* obj : objects_) {
		shader->use();

		//Set view and projection matrix of the world
		shader->setMat4("view", camera_->getView());
		shader->setMat4("projection", camera_->getProj());

		//Set view position for lighting
		shader->setVec3("viewPos", camera_->getPos());

		obj->render(shader);
	}

	//Disable face culling (Default set to CCW)
	glDisable(GL_CULL_FACE);
}

void Renderer::renderLightMeshes(Camera* camera_, ShaderManager::HandleType shaderHandle_, std::vector<Light*> lights_)
{
	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);

	//Enable face culling (Default set to CCW)
	glEnable(GL_CULL_FACE);

	for (Light* light : lights_) {
		shader->use();

		//Set view and projection matrix of the world
		shader->setMat4("view", camera_->getView());
		shader->setMat4("projection", camera_->getProj());

		//Set view position for lighting
		shader->setVec3("viewPos", camera_->getPos());

		light->render(shader);
	}

	//Disable face culling (Default set to CCW)
	glDisable(GL_CULL_FACE);
}

void Renderer::renderSkybox(Camera* camera_, Skybox* skybox_)
{
	Shader* shader = skybox_->getAttachedShader();

	shader->use();

	//Set view and projection matrix of the world
	//Convert the view matrix to a 3x3 to remove translation
	glm::mat4 skyboxView = glm::mat4(glm::mat3(camera_->getView()));
	shader->setMat4("view", skyboxView);
	shader->setMat4("projection", camera_->getProj());

	skybox_->render(shader);
}

void Renderer::renderFramebuffer(ShaderManager::HandleType shaderHandle_, Framebuffer* framebuffer_)
{
	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);
	shader->use();

	//Disable depth testing so that the plane is properly rendered and not culled
	glDisable(GL_DEPTH_TEST);

	framebuffer_->render(shader);

	//Enable depth testing after the plane is rendered
	glEnable(GL_DEPTH_TEST);
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