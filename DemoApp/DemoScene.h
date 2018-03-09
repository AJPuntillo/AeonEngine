#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Light.h>
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>
#include <AeonEngine/Engine/Rendering/3D/Framebuffer.h>
#include <AeonEngine/Engine/Rendering/3D/GameObject.h>
#include <AeonEngine/Engine/Rendering/Grid/Board.h>
#include <AeonEngine/Engine/Rendering/Particles/ParticleEngine.h>
#include <AeonEngine/Engine/Rendering/Pieces/Piece.h>

class DemoScene : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene();
	virtual ~DemoScene();

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
	AEON_ENGINE::ShaderManager::HandleType m_shaderLighting;
	AEON_ENGINE::ShaderManager::HandleType m_shaderContainer;
	AEON_ENGINE::ShaderManager::HandleType m_shaderLamp;
	AEON_ENGINE::ShaderManager::HandleType m_shaderSkybox;
	AEON_ENGINE::ShaderManager::HandleType m_shaderFramebuffer;
	AEON_ENGINE::ShaderManager::HandleType m_shaderInstancing;
	//GameObjects
	AEON_ENGINE::GameObject* model_cube;
	AEON_ENGINE::GameObject* model_nanosuit;
	AEON_ENGINE::GameObject* model_nanosuit2;
	AEON_ENGINE::GameObject* model_nanosuit3;
	AEON_ENGINE::GameObject* model_nanosuit4;
	AEON_ENGINE::GameObject* model_nanosuit5;
	AEON_ENGINE::GameObject* model_nanosuit6;
	AEON_ENGINE::GameObject* model_nanosuit7;
	AEON_ENGINE::GameObject* model_nanosuit8;
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
	std::vector<AEON_ENGINE::GameObject*> objectList;
	std::vector<AEON_ENGINE::GameObject*> objectList2;
	std::vector<AEON_ENGINE::Light*> lightList;

	//Board
	AEON_ENGINE::Board* board;

	//Piece
	AEON_ENGINE::Piece* piece;

	//Particles
	AEON_ENGINE::GameObject* particleObject;
	AEON_ENGINE::ParticleEmitter* emitter;

	//Timing
	float m_deltaTime = 0.0f; //Time between current frame and last frame
};

#endif