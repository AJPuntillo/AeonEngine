#include "DemoGame.h"

#include "DemoScene.h"
#include "DemoScene2.h"
#include "TutorialScene.h"

using namespace AEON_ENGINE;

DemoGame::DemoGame()
{
	//Empty
}

DemoGame::~DemoGame()
{
	delete m_currentScene;
	m_currentScene = nullptr;
}

bool DemoGame::initialize() {

	//Default scene you want to load
	//Change TutorialScene() to which ever scene you want/have created
	//**Remember that it must be included at the top of this file
	m_currentScene = new DemoScene();

	m_currentScene->initialize();

	return true;
}

void DemoGame::processInput()
{
	m_currentScene->processInput();

	//Quick and sloppy controls to switch out scenes
	//We should really come back and flush this out nicer when the time provides
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_1)) {
		switchScene(0);
	}
	else if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_2)) {
		switchScene(1);
	}
}

void DemoGame::update(float deltaTime_)
{
	m_currentScene->update(deltaTime_);
}

void DemoGame::prerender()
{
	m_currentScene->prerender();
}


void DemoGame::render()
{
	m_currentScene->render();
}

void DemoGame::postrender()
{
	m_currentScene->postrender();
}


void DemoGame::draw()
{
	m_currentScene->draw();
}

void DemoGame::loadScene(int sceneIndex_)
{

}

void DemoGame::switchScene(int scene)
{

	if (scene == m_currentSceneIndex) {
		return;
	}

	switch (scene) {
	case 0:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new DemoScene();
		break;

	case 1:
		delete m_currentScene;
		m_currentScene = nullptr;

		m_currentScene = new DemoScene2();
		break;

	default:
		return;
	}

	m_currentSceneIndex = scene;

	m_currentScene->initialize();
}
