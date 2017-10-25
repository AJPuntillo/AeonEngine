#include "EngineCore.h"

using namespace AEON_ENGINE;

//Initialize static variables
std::unique_ptr<EngineCore> EngineCore::engineCoreInstance(nullptr);
Window* EngineCore::m_window(nullptr);

EngineCore::EngineCore()
{
	//Empty
}

EngineCore::~EngineCore()
{
	//Tell the engine to delete the game on shutdown
	delete gameInterface;
	gameInterface = nullptr;

	TerminateGame();
}

void EngineCore::TerminateGame()
{
	exit(0);

	m_window->shutdown();
	m_window = nullptr;

	SDL_Quit();
}

EngineCore* EngineCore::getInstance()
{
	//Check to see if you have already been initialized
	if (engineCoreInstance.get() == nullptr) {
		engineCoreInstance.reset(new EngineCore);
	}

	return engineCoreInstance.get();
}

bool EngineCore::initialize()
{
	m_window = new Window();
	m_window->initialize("Demo", 800, 600, 0);

	//Check if the game interface exists
	if (gameInterface != nullptr) {
		if (gameInterface->initialize() == false) {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

void EngineCore::run()
{
	//Set the isRunning state to true the first time this method is called
	m_isRunning = true;

	//Maintain the game loop while this engine is running
	while (m_isRunning) {
		//Update the InputManager
		m_inputManager.update(); //**Pointer?
		//Take in Input
		updateInput();
		//Update the world
		update();
		//Render the 3D
		render();
		//Draw 2D ontop of the 3D
		draw();
	}
}

void EngineCore::update()
{
	gameInterface->update();
}

void EngineCore::render()
{
	gameInterface->render();
}

void EngineCore::draw()
{
	gameInterface->draw();
}

void EngineCore::updateInput()
{
	SDL_Event event;

	//We toss in the event as a reference so that SDL_PollEvent will modifiy it internally and
	//then leave it for us to look at.
	while (SDL_PollEvent(&event)) {

		//If we click on the [ X ] in the top corner, then we want the Gameloop to end
		if (event.type == SDL_QUIT)
			m_isRunning = false;

		if (event.type == SDL_KEYDOWN)
			m_inputManager.pressKey(event.key.keysym.sym);

		if (event.type == SDL_KEYUP)
			m_inputManager.releaseKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEBUTTONDOWN)
			m_inputManager.pressKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEBUTTONUP)
			m_inputManager.releaseKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEMOTION) {
			m_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			//std::cout << event.motion.x << " " << event.motion.y << std::endl; //Print out to see mouse position on screen
		}
	}
}