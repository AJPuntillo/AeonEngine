#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Light.h>
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>
#include <AeonEngine/Engine/Rendering/3D/Framebuffer.h>
#include <AeonEngine/Engine/Rendering/3D/GameObject.h>

#include "../Gameplay/Grid/Board.h"

class Scene_Main : public AEON_ENGINE::SceneInterface
{
public:
	Scene_Main();
	virtual ~Scene_Main();

	virtual bool initialize();
	virtual void processInput();
	virtual void update(float deltaTime_);
	virtual void prerender();
	virtual void render();
	virtual void postrender();
	virtual void draw();

private:
	//Camera
	AEON_ENGINE::Camera* m_camera;
	//Renderer
	AEON_ENGINE::Renderer* m_renderer;
	//Shader Program
	AEON_ENGINE::ShaderManager::HandleType m_shaderBoard;
	AEON_ENGINE::ShaderManager::HandleType m_shaderPieces;
	AEON_ENGINE::ShaderManager::HandleType m_shaderSkybox;
	AEON_ENGINE::ShaderManager::HandleType m_shaderFramebuffer;
	//GameObjects
	AEON_ENGINE::GameObject* m_objBoard;
	//Lights
	AEON_ENGINE::Light* dirLight;
	//Skybox
	AEON_ENGINE::Skybox* skybox;
	std::vector<std::string> skyboxFaces;
	//Framebuffer
	AEON_ENGINE::Framebuffer* framebuffer;
	//Model Lists
	std::vector<AEON_ENGINE::GameObject*> objectList;
	std::vector<AEON_ENGINE::Light*> lightList;
	//Board
	Board* m_board;
	//Timing
	float m_deltaTime = 0.0f; //Time between current frame and last frame
};

#endif