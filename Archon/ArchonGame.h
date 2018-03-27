#ifndef ARCHONGAME_H
#define ARCHONGAME_H

#include <AeonEngine/Engine/Core/EngineCore.h>
#include <AeonEngine/Engine/Core/SceneInterface.h>
#include <AeonEngine/Engine/Core/GameInterface.h>

class ArchonGame : public AEON_ENGINE::GameInterface
{
public:
	ArchonGame();
	~ArchonGame();

	virtual bool initialize() override;
	virtual void processInput() override;
	virtual void update(float deltaTime_) override;
	virtual void prerender() override;
	virtual void render() override;
	virtual void postrender() override;
	virtual void draw() override;
	virtual void loadScene(int sceneIndex_) override;

private:
	void switchScene(int scene);

	int m_currentSceneIndex = 0;
	AEON_ENGINE::SceneInterface* m_currentScene = nullptr;
};

#endif