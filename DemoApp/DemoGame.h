#ifndef DEMOGAME_H
#define DEMOGAME_H

#include <AeonEngine/Engine/Core/EngineCore.h>
#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Core/GameInterface.h>

class DemoGame : public AEON_ENGINE::GameInterface
{
public:
	DemoGame();
	~DemoGame();

	virtual bool initialize() override;
	virtual void processInput() override;
	virtual void update() override;
	virtual void render() override;
	virtual void draw() override;


private:
	void switchScene(int scene);

	int m_currentSceneIndex = 0;
	AEON_ENGINE::SceneInterface* m_currentScene = nullptr;
};

#endif