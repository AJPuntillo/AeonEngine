#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Window.h"
#include "GameInterface.h"
#include "../Graphics/Shader.h"
#include "../Camera/Camera.h"
#include "../Events/InputManager.h"

#include <memory>

//***
//This class needs to be changed for the future
//Right now it initializes the window and shader but that should not be determined inside this class
//This class should only initialize engine specific classes and any other user-specific preferences (eg. window size, which shaders to use) should be create somewhere else
//***

namespace AEON_ENGINE {

	class EngineCore 
	{
	public:
		//Delete the default constructors so that they are not created
		//Allows the creation of a Singleton
		//Can only ever create one object of this class, and by deleting
		//these constructors we now have control over how it is created
		EngineCore(const EngineCore&) = delete;
		EngineCore(EngineCore&&) = delete;
		EngineCore& operator=(const EngineCore&) = delete;
		EngineCore& operator=(EngineCore&&) = delete;

		//Instance getter to allow them to get the current version of this class
		//Means that only one will ever exist at any given time
		//Can be called and accessed from any point within the engine
		//If no instance of this class exists, it will be created
		static EngineCore* getInstance();
		static void TerminateGame();

		bool initialize();
		void run();
		void update();
		void render();
		void draw();

		//Getters
		Window* getWindow() const			{ return m_window; };
		Shader* getShader() const			{ return m_shaderProgram;}
		SDL_Keycode getKeyPressed() const	{ return keyDown; };
		InputManager getInputManager()		{ return m_inputManager; }

		//This is the pointer to the abstract Game
		GameInterface* gameInterface = nullptr;

	private:
		//Privte constructor and destructor -- for Singleton
		EngineCore();
		~EngineCore();

		void updateInput();

		//Hold the instance of itself
		//Friend function allows automatic cleanup and memory management
		static std::unique_ptr<EngineCore> engineCoreInstance;
		friend std::default_delete<EngineCore>;

		//Window				//Defaults
		static Window* m_window;
		//Shader Program
		Shader* m_shaderProgram	= nullptr;
		//Game Loop
		bool m_isRunning = false;
		//Checking input
		InputManager m_inputManager;
		SDL_Keycode keyDown;
	};

}

#endif