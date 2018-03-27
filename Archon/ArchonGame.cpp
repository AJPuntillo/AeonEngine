#include "ArchonGame.h"

#include "Scenes/Scene_Main.h"
#include "Scenes/Scene_Menu.h"

using namespace AEON_ENGINE;

ArchonGame::ArchonGame()
{
	//Empty
}

ArchonGame::~ArchonGame()
{
	delete m_currentScene;
	m_currentScene = nullptr;
}

bool ArchonGame::initialize() {

	//Default scene you want to load
	m_currentScene = new Scene_Menu;

	m_currentScene->initialize();

	return true;
}

void ArchonGame::processInput()
{
	m_currentScene->processInput();
}

void ArchonGame::update(float deltaTime_)
{
	m_currentScene->update(deltaTime_);
}

void ArchonGame::prerender()
{
	m_currentScene->prerender();
}


void ArchonGame::render()
{
	m_currentScene->render();
}

void ArchonGame::postrender()
{
	m_currentScene->postrender();
}


void ArchonGame::draw()
{
	m_currentScene->draw();
}

void ArchonGame::loadScene(int sceneIndex_)
{
	switch (sceneIndex_) {
	case 0:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new Scene_Menu();
		break;
	case 1:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new Scene_Main();
		break;
	default:
		return;
	}

	m_currentSceneIndex = sceneIndex_;

	m_currentScene->initialize();
}

void ArchonGame::switchScene(int scene)
{

	if (scene == m_currentSceneIndex) {
		return;
	}

	switch (scene) {
	case 0:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new Scene_Menu();
		break;
	case 1:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new Scene_Main();
		break;
	default:
		return;
	}

	m_currentSceneIndex = scene;

	m_currentScene->initialize();
}
