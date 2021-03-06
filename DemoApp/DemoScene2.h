#ifndef DEMOSCENE2_H
#define DEMOSCENE2_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>

class DemoScene2 : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene2();
	virtual ~DemoScene2();

	virtual bool initialize();
	virtual void processInput();
	virtual void update(float deltaTime_);
	virtual void prerender();
	virtual void render();
	virtual void postrender();
	virtual void draw();

private:
	AEON_ENGINE::Camera camera;
};

#endif
