#include <AeonEngine/Engine/Core/Window.h>
#include <AeonEngine/Engine/Graphics/Shader.h>

using namespace AEON_ENGINE;

#include "DemoGame.h"

int main(int argc, char* args[]) {
	//Grab an instance of the engine and then tell it that it has a game attached; 
	//IMPORTANT: Needs to be before the initialize()
	EngineCore::getInstance()->gameInterface = new DemoGame();

	//Create the first instance of our engine
	if (EngineCore::getInstance()->initialize()) {
		//Start the Game Loop
		EngineCore::getInstance()->run();
	}

	return 0;
}