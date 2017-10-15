#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>

class DemoScene : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene();
	virtual ~DemoScene();

	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void draw();

private:
	unsigned int VBO, VAO;
	//Camera
	AEON_ENGINE::Camera* m_camera;
	//Shader Program
	AEON_ENGINE::Shader* m_shaderProgram = nullptr;
	//Renderer
	AEON_ENGINE::Renderer* m_renderer;
	//Meshes
	AEON_ENGINE::Model* testModel;

	//Makeshift bool to capture mouse, will need to change later (Possibly in its own method of the InputManager)
	bool captureMouse = true;
};

#endif
