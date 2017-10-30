#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/PrimitiveModel.h>
#include <AeonEngine/Engine/Rendering/3D/Light.h>
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>

class DemoScene : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene();
	virtual ~DemoScene();

	virtual bool initialize();
	virtual void processInput();
	virtual void update();
	virtual void render();
	virtual void draw();

private:
	unsigned int VBO, VAO;
	//Camera
	AEON_ENGINE::Camera* m_camera;
	//Shader Program
	AEON_ENGINE::Shader* m_shaderProgram = nullptr;
	AEON_ENGINE::Shader* m_containerProgram = nullptr;
	AEON_ENGINE::Shader* m_skyboxProgram = nullptr;
	//Renderer
	AEON_ENGINE::Renderer* m_renderer;
	//Models
	AEON_ENGINE::PrimitiveModel* testModel;
	AEON_ENGINE::Model* testModel2;
	//Light List
	AEON_ENGINE::Light* spotLight;
	AEON_ENGINE::Light* pointLight;
	//Skybox
	AEON_ENGINE::Skybox* skybox;
	std::vector<std::string> skyboxFaces;
	//Model Lists
	std::vector<AEON_ENGINE::Entity*> modelList;
	std::vector<AEON_ENGINE::Light*> lightList;

	//Makeshift bool to capture mouse, will need to change later (Possibly in its own method of the InputManager)
	bool captureMouse = true;

	//**These variables are used for a quick timestep
	//Timing
	float deltaTime = 0.0f; //Time between current frame and last frame
	float lastFrame = 0.0f; //Time of last frame
};

#endif