#include "Window.h"

using namespace AEON_ENGINE;

Window::Window()
{
	//Empty
}


Window::~Window()
{
	shutdown();
}

bool Window::initialize(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
	//Initialize SDL and check if it succeded
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "Failed to initialize SDL!" << std::endl;
		return false;
	}

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE)
		flags |= SDL_WINDOW_HIDDEN;

	if (currentFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	if (currentFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	//Create the window -- SDL_WINDOW_CENTERED is a built-in SDL parameter that centers based on the screen width/height
	m_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	//Window creation error checking
	if (!m_window) {
		std::cout << "Failed to initialize window!" << std::endl;
		shutdown();
		return false;
	}

	//Pass in the window created above to bind it to the context
	m_context = SDL_GL_CreateContext(m_window);
	//Context binding error checking
	if (m_context == nullptr) {
		std::cout << "Failed to create SDL_GL context!" << std::endl;
		shutdown();
		return false;
	}

	//Set the Attributes that will be used within the window
	setAttributes();

	//Initialize glew
	GLenum err = glewInit();
	//glewInit error checking
	if (err != GLEW_OK) {
		std::cout << "glewInit failed, aborting." << std::endl;
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		return false;
	}

	//Check the OpenGL version
	std::printf("***     OpenGL Version: %s     ***\n", glGetString(GL_VERSION));

	//BG colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SDL_GL_SetSwapInterval(0); //Set VSYNC

	//Enable alpha blend
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Tells the GPU to test for depth when rendering
	glEnable(GL_DEPTH_TEST); //LESSON LEARNED: Don't enable depth testing unless you plan on clearing the depth buffer in the render loop

	return true;
}

void Window::shutdown()
{
	//Clean up the window
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(m_window); //Swapping the window for double bufferring
}

void Window::lockMouse()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);
}

void Window::unlockMouse()
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_CaptureMouse(SDL_FALSE);
}

void Window::setAttributes()
{
	//Ignore any depricated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//Set up the version of OpenGL that will be used (3.3 covers MOST computers)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//Double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Depth buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}