#include "DemoScene2.h"

using namespace AEON_ENGINE;

DemoScene2::DemoScene2()
{
	//Empty
}

DemoScene2::~DemoScene2()
{
	//Empty
}

bool DemoScene2::initialize()
{
	//**Lock Mouse
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);

	return true;
}

void DemoScene2::update()
{

}

void DemoScene2::render()
{
	//**Store shader/window variables -- for convenience
	//GLuint shaderID = EngineCore::getInstance()->getShader()->getShaderProgram();
	int SCREEN_WIDTH = EngineCore::getInstance()->getWindow()->getScreenWidth();
	int SCREEN_HEIGHT = EngineCore::getInstance()->getWindow()->getScreenHeight();

	//Rendering
	glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw our first triangle
	//EngineCore::getInstance()->getShader()->use();


	//Swap buffers
	EngineCore::getInstance()->getWindow()->swapBuffers();
}

void DemoScene2::draw()
{

}