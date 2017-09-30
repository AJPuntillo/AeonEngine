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
	virtual void update();
	virtual void render();
	virtual void draw();

private:
	AEON_ENGINE::Camera camera;
};

#endif
