#include "Scene_Menu.h"
#include <glm/gtx/compatibility.hpp>
using namespace AEON_ENGINE;

Scene_Menu::Scene_Menu()
{
	//Empty
}

Scene_Menu::~Scene_Menu()
{
	delete m_camera;
	m_camera = nullptr;

	delete m_renderer;
	m_renderer = nullptr;

	delete dirLight;
	dirLight = nullptr;

	delete skybox;
	skybox = nullptr;

	delete framebuffer;
	framebuffer = nullptr;

	menu_music.stop();

	delete m_textRenderer;
	m_textRenderer = nullptr;

	for (Text* text : m_textList) {
		delete text;
		text = nullptr;
	}
}

bool Scene_Menu::initialize()
{
	//Lock Mouse
	EngineCore::getInstance()->getWindow()->lockMouse();

	//Camera
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 10.0f);

	//Renderer
	m_renderer = new Renderer();

	//Shaders
	m_shaderBoard = ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/lightingShaderVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");
	m_shaderSkybox = ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");
	m_shaderText = ShaderManager::getInstance()->addShader("shader_text", "Resources/Shaders/textVert.glsl", "Resources/Shaders/textFrag.glsl");

	//Lights
	dirLight = new Light(LIGHT_DIRECTIONAL, true);
	//dirLight->setDirection(glm::vec3(-0.5f, -0.4f, -0.4f));
	dirLight->setDirection(glm::vec3(-0.2f, -0.3f, 0.2f));
	dirLight->setLightIntensity(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f));
	dirLight->setShininess(16.0f);
	lightList.push_back(dirLight);

	//Skybox
	skyboxFaces = {
		"Resources/Cubemaps/hw_nightsky/nightsky_rt.tga",
		"Resources/Cubemaps/hw_nightsky/nightsky_lf.tga",
		"Resources/Cubemaps/hw_nightsky/nightsky_up1.tga",
		"Resources/Cubemaps/hw_nightsky/nightsky_dn.tga",
		"Resources/Cubemaps/hw_nightsky/nightsky_bk.tga",
		"Resources/Cubemaps/hw_nightsky/nightsky_ft.tga"
	};
	skybox = new Skybox(skyboxFaces, m_shaderSkybox);

	//Framebuffer
	framebuffer = new Framebuffer(EngineCore::getInstance()->getWindow());

	//GameObjects

	//Audio
	m_audioEngine.init();
	menu_music = m_audioEngine.loadMusic("Resources/Audio/Music/Ove_Heaven_Sings.ogg");
	menu_music.play(-1, 50);

	//Text
	m_textRenderer = new TextRenderer();
	m_textRenderer->init("Resources/Fonts/Arkhip_font.ttf");

	text_title = new Text("ARCHON", 100, 400, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_textList.push_back(text_title);

	text_start = new Text("START", 100, 140, 0.6f, glm::vec3(1.0f, 1.0f, 1.0f));
	text_start->setHoverColour(glm::vec3(1.0f, 0.6f, 0.6f));
	text_start->toggleHoverState();
	m_textList.push_back(text_start);

	text_quit = new Text("QUIT", 100, 100, 0.6f, glm::vec3(1.0f, 1.0f, 1.0f));
	text_quit->setHoverColour(glm::vec3(1.0f, 0.6f, 0.6f));
	m_textList.push_back(text_quit);

	return true;
}

void Scene_Menu::processInput()
{
	//Camera movement with mouse
	//m_camera->processMouse(EngineCore::getInstance()->getInputManager());

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	//Toggle Fullscreen
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_F1))
		EngineCore::getInstance()->getWindow()->toggleFullscreen();

	//Navigate Menu
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_UP)) {
		navigateMenu(1);
	}

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_DOWN)) {
		navigateMenu(0);
	}

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_RETURN) || EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_z)) {
		selectMenu();
	}
}

void Scene_Menu::update(float deltaTime_)
{
	//Update the deltaTime for the processInput
	m_deltaTime = deltaTime_;

	//Update the framebuffer incase of screen size changes (Might not want to check every update, rather only check when screensize changes)
	framebuffer->updateFramebufferSize(EngineCore::getInstance()->getWindow());

	m_textRenderer->UpdateTextPosition(EngineCore::getInstance()->getWindow(), m_textList);

	m_camera->setYaw(m_camera->getYaw() + (0.01f + deltaTime_));
}

void Scene_Menu::prerender()
{
	//Bind to the framebuffer and draw a scene as we normally would to colour texture; Must be called at the start of render
	framebuffer->bindBuffer();

	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();
}

void Scene_Menu::render()
{
	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	m_renderer->render(m_camera, m_shaderBoard, objectList, lightList);
	m_renderer->renderSkybox(m_camera, skybox);
}

void Scene_Menu::postrender()
{
	//Must render the framebuffer last
	m_renderer->renderFramebuffer(m_shaderFramebuffer, framebuffer);

	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void Scene_Menu::draw()
{
	m_textRenderer->RenderText(EngineCore::getInstance()->getWindow(), m_shaderText, m_textList);
}

void Scene_Menu::navigateMenu(int dir_)
{
	switch (dir_) {
	case 0:
		if (hov == 0) {
			text_start->toggleHoverState();
			text_quit->toggleHoverState();
		}
		hov++;
		if (hov > 1)
			hov = 1;
		break;

	case 1:
		if (hov == 1) {
			text_start->toggleHoverState();
			text_quit->toggleHoverState();
		}
		hov--;
		if (hov < 0)
			hov = 0;
		break;
	}
}

void Scene_Menu::selectMenu()
{
	if (text_start->isHovered) {
		EngineCore::getInstance()->gameInterface->loadScene(1);
	}
	else if (text_quit->isHovered) {
		EngineCore::TerminateGame();
	}
}
