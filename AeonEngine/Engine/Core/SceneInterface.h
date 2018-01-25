#ifndef SCENEINTERFACE_H
#define SCENEINTERFACE_H

#include "EngineCore.h"

//***
//SCENE INTERFACE CLASS:
//Interface class.
//Acts as the "container" for the currently active scene.
//**

namespace AEON_ENGINE {

	class SceneInterface
	{
	public:
		SceneInterface() {};
		virtual ~SceneInterface() {};

		//By saying virtual and = 0 we delete the method and force the inherited classes to create these and flush them out
		virtual bool initialize() = 0;
		virtual void processInput() = 0;
		virtual void update(float deltaTime_) = 0;
		virtual void prerender() = 0;
		virtual void render() = 0;
		virtual void postrender() = 0;
		virtual void draw() = 0;

	protected:
		EngineCore* engine = EngineCore::getInstance();
	};

}

#endif