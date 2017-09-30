#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> //Glew must be included first
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include <iostream>

//Set up the GL3_Prototypes
#define GL3_PROTOTYPES 1

namespace AEON_ENGINE {

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 }; //Setting these to certain binary values so that all three options can be bitwise'd together if the user desires more than one at the same time, rather than setting up multiple bools for each -- Much more efficient

	class Window
	{
	public:
		Window();
		~Window();

		bool initialize(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		void swapBuffers();
		void shutdown();

		//Getters
		SDL_Window* getWindow() const	{ return m_window; };
		int getScreenWidth() const		{ return m_screenWidth; };
		int getScreenHeight() const		{ return m_screenHeight; };

	private:
		void setAttributes();

		//Window					//Defaults
		SDL_Window* m_window		= nullptr;
		SDL_GLContext m_context;
		//Screen Size
		int m_screenWidth			= 800;
		int m_screenHeight			= 600;
	};

}

#endif