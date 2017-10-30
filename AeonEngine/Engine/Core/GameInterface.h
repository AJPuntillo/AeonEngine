#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

//***
//GAME INTERFACE CLASS:
//Interface class.
//The "container" of the game. Manages the scenes of the game and processes each active scene's Update, Render, and Input.
//***

namespace AEON_ENGINE {

	class GameInterface
	{
	public:
		GameInterface() {};
		virtual ~GameInterface() {};

		//By saying virtual and = 0 we delete the method and force the inherited classes to create these and flush them out
		virtual bool initialize() = 0;
		virtual void processInput() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void draw() = 0;
	};

}

#endif