#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Camera/Camera.h>
#include <AeonEngine/Engine/Rendering/3D/Cube.h>

class DemoScene : public AEON_ENGINE::SceneInterface
{
public:
	DemoScene();
	virtual ~DemoScene();

	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void draw();

private:
	unsigned int VBO, VAO;
	AEON_ENGINE::Camera camera;
};

#endif
