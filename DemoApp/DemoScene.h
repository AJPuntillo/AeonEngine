#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/PrimitiveModel.h>
#include <AeonEngine/Engine/Rendering/3D/Light.h>
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>
#include <AeonEngine/Engine/Rendering/3D/Framebuffer.h>

class DemoScene : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene();
	virtual ~DemoScene();

	virtual bool initialize();
	virtual void processInput();
	virtual void update(float deltaTime_);
	virtual void render();
	virtual void draw();

private:
	//Camera
	AEON_ENGINE::Camera* m_camera;
	//Shader Program
	AEON_ENGINE::Shader* m_shaderProgram = nullptr;
	AEON_ENGINE::Shader* m_containerProgram = nullptr;
	AEON_ENGINE::Shader* m_skyboxProgram = nullptr;
	AEON_ENGINE::Shader* m_framebufferProgram = nullptr;
	AEON_ENGINE::Shader* m_instanceProgram = nullptr;
	//Renderer
	AEON_ENGINE::Renderer* m_renderer;
	//Models
	AEON_ENGINE::PrimitiveModel* testModel;
	AEON_ENGINE::Model* testModel2;
	//Light List
	AEON_ENGINE::Light* dirLight;
	AEON_ENGINE::Light* pointLight;
	AEON_ENGINE::Light* pointLight2;
	//Skybox
	AEON_ENGINE::Skybox* skybox;
	std::vector<std::string> skyboxFaces;
	//Framebuffer
	AEON_ENGINE::Framebuffer* framebuffer;
	//Model Lists
	std::vector<AEON_ENGINE::Entity*> modelList;
	std::vector<AEON_ENGINE::Light*> lightList;

	//Timing
	float m_deltaTime = 0.0f; //Time between current frame and last frame

	std::vector<AEON_ENGINE::Light*> m_pointList;
	std::vector<AEON_ENGINE::Light*> m_directionalList;
	unsigned int lightListSize = 0;
};

#endif