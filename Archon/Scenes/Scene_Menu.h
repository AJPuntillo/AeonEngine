#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>
#include <AeonEngine/Engine/Rendering/3D/Model.h>
#include <AeonEngine/Engine/Rendering/3D/Light.h>
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>
#include <AeonEngine/Engine/Rendering/3D/Framebuffer.h>
#include <AeonEngine/Engine/Rendering/3D/GameObject.h>
#include <AeonEngine/Engine/Audio/Audio.h>
#include <AeonEngine/Engine/Rendering/2D/TextRenderer.h>

#include "../Gameplay/Grid/Board.h"

class Scene_Menu : public AEON_ENGINE::SceneInterface
{
public:
	Scene_Menu();
	virtual ~Scene_Menu();

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
	AEON_ENGINE::ShaderManager::HandleType m_shaderSkybox;
	AEON_ENGINE::ShaderManager::HandleType m_shaderFramebuffer;
	AEON_ENGINE::ShaderManager::HandleType m_shaderText;
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
	//Audio
	AEON_ENGINE::Audio m_audioEngine;
	AEON_ENGINE::Music menu_music;
	//Text
	AEON_ENGINE::TextRenderer* m_textRenderer;
	AEON_ENGINE::Text* text_title;
	AEON_ENGINE::Text* text_start;
	AEON_ENGINE::Text* text_quit;
	std::vector<AEON_ENGINE::Text*> m_textList;

	//Sloppy menu navigation, for quick use
	void navigateMenu(int dir_);
	void selectMenu();
	int hov = 0;

};

#endif