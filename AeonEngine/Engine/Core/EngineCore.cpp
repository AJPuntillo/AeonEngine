#include "EngineCore.h"
#include "Timer.h"

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

bool EngineCore::initialize(std::string windowName, int windowHeight, int windowWidth, int windowFlags)
{
	m_window = new Window();
	m_window->initialize(windowName, windowHeight, windowWidth, windowFlags);

	m_inputManager = new InputManager();

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

void EngineCore::run(int maxFPS_, bool printTimer_)
{
	//Set the isRunning state to true the first time this method is called
	m_isRunning = true;

	//Timestep/FPS Limiter
	Timer timer;
	timer.startTimer();

	//Maintain the game loop while this engine is running
	while (m_isRunning) {
		//Begin getting frameticks; Must be at the start of the loop
		timer.updateFrameTicks();
		//Take in Input
		updateInput();
		//Update the world
		update(timer.getDeltaTime());
		//Prerender
		prerender();
		//Render the 3D
		render();
		//Draw 2D ontop of the 3D
		draw();
		//Postrender; So that objects in draw will not be left out at the end of a render call
		postrender();
		//FPS Limiter; limits the frames per second and keeps the main loop running at a specified pace
		SDL_Delay(timer.getSleepTime(maxFPS_));

		//If FPS/Delta Time need to be printed out for debugging
		if (printTimer_) {
			std::cout << "FPS: " << (1.0f / timer.getDeltaTime()) << std::endl;
			std::cout << "Delta Time: " << timer.getDeltaTime() << std::endl;
		}
	}
}

void EngineCore::updateInput()
{
	//Update the InputManager
	m_inputManager->update();

	SDL_Event event;

	//We toss in the event as a reference so that SDL_PollEvent will modifiy it internally and
	//then leave it for us to look at.
	while (SDL_PollEvent(&event)) {

		//If we click on the [ X ] in the top corner, then we want the Gameloop to end
		if (event.type == SDL_QUIT)
			m_isRunning = false;

		if (event.type == SDL_KEYDOWN)
			m_inputManager->pressKey(event.key.keysym.sym);

		if (event.type == SDL_KEYUP)
			m_inputManager->releaseKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEBUTTONDOWN)
			m_inputManager->pressKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEBUTTONUP)
			m_inputManager->releaseKey(event.key.keysym.sym);

		if (event.type == SDL_MOUSEMOTION)
			m_inputManager->setMouseCoords(event.motion.x, event.motion.y);

		if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
			m_window->unlockMouse();

		if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			m_window->lockMouse();

		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			onResize(event.window.data1, event.window.data2);
		}

		//if (event.type == SDL_MOUSEWHEEL)
		//**Might need to add a mouse wheel function to the Input Manager
	}

	gameInterface->processInput();
}

void EngineCore::update(float deltaTime_)
{
	gameInterface->update(deltaTime_);
}

void EngineCore::prerender()
{
	gameInterface->prerender();
}

void EngineCore::render()
{
	gameInterface->render();
}

void EngineCore::postrender()
{
	gameInterface->postrender();
}

void EngineCore::draw()
{
	gameInterface->draw();
}

void EngineCore::onResize(int newWidth_, int newHeight_)
{
	m_window->setWindowSize(newWidth_, newHeight_);
	glViewport(0, 0, m_window->getScreenWidth(), m_window->getScreenHeight());
}