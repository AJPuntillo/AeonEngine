#ifndef SCENEINTERFACE_H
#define SCENEINTERFACE_H

#include "EngineCore.h"

namespace AEON_ENGINE {

	//Interface Class
	class SceneInterface
	{
	public:
		SceneInterface() {};
		virtual ~SceneInterface() {};

		//By saying virtual and = 0 we delete the method and force the inherited classes to create these and flush them out
		virtual bool initialize() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void draw() = 0;
	};

}

#endif