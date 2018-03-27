#include "Scene_Main.h"
#include <glm/gtx/compatibility.hpp>
using namespace AEON_ENGINE;

Scene_Main::Scene_Main()
{
	//Empty
}

Scene_Main::~Scene_Main()
{
	delete m_camera;
	m_camera = nullptr;

	delete m_renderer;
	m_renderer = nullptr;

	delete m_textRenderer;
	m_textRenderer = nullptr;

	delete m_objBoard;
	m_objBoard = nullptr;

	delete dirLight;
	dirLight = nullptr;

	delete skybox;
	skybox = nullptr;

	delete framebuffer;
	framebuffer = nullptr;

	delete m_board;
	m_board = nullptr;

	delete m_gm;
	m_gm = nullptr;
}

bool Scene_Main::initialize()
{
	//Lock Mouse
	EngineCore::getInstance()->getWindow()->lockMouse();

	//Camera
	m_camera = new Camera(glm::vec3(-2.75f, 6.75f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -50.0f);
	//m_camera = new Camera(glm::vec3(3.5f, 5.0f, 12.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -50.0f);
	//m_camera = new Camera(glm::vec3(3.5f, 3.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -50.0f);


	//Renderer
	m_renderer = new Renderer();

	//Shaders
	m_shaderBoard = ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/lightingShaderVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");
	m_shaderParticles = ShaderManager::getInstance()->addShader("shader_container", "Resources/Shaders/simpleParticle_Vert.glsl", "Resources/Shaders/simpleParticle_Frag.glsl");
	m_shaderSkybox = ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");

	//Lights
	dirLight = new Light(LIGHT_DIRECTIONAL, false);
	dirLight->setDirection(glm::vec3(-0.0f, -0.3f, 0.2f));
	dirLight->setLightIntensity(glm::vec3(0.8f, 0.8f, 1.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.4f, 0.4f, 0.4f));
	dirLight->setShininess(16.0f);
	lightList.push_back(dirLight);

	//Old light settings
	//dirLight->setDirection(glm::vec3(-0.5f, -0.4f, -0.4f));
	//dirLight->setDirection(glm::vec3(-0.2f, -0.3f, 0.2f)); 
	//dirLight->setDirection(glm::vec3(0.0f, -0.4f, 0.6f));
	//dirLight->setLightIntensity(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f));
	//dirLight->setLightIntensity(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f));
	//pointLight = new Light(LIGHT_POINT, true);
	//pointLight->setAttenuation(1.0f, 0.014f, 0.00007f);
	//pointLight->setLightIntensity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f));
	//pointLight->setShininess(2.0f);
	//pointLight->transform.setPosition(glm::vec3(3.5f, 2.75f, 3.5f));
	//lightList.push_back(pointLight);

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

	//Board layout
	//0: GRASS
	//1: LAVA
	//2: RIVER
	//4: MOUNTAIN
	std::vector<char> boardLayout = {
		0, 0, 2, 0, 0, 1, 0, 0,
		0, 0, 3, 0, 2, 3, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 3, 2, 0, 3, 0, 0,
		0, 0, 1, 0, 0, 2, 0, 0
	};

	//Piece layout
	//0: NONE
	//1: EARTH	(P1)
	//2: WATER	(P1)
	//3: FIRE	(P1)
	//4: EARTH	(P2)
	//5: WATER	(P2)
	//6: FIRE	(P2)
	std::vector<char> pieceLayout = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 4,
		2, 0, 0, 0, 0, 0, 0, 5,
		3, 0, 0, 0, 0, 0, 0, 6,
		3, 0, 0, 0, 0, 0, 0, 6,
		2, 0, 0, 0, 0, 0, 0, 5,
		1, 0, 0, 0, 0, 0, 0, 4,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	m_board = new Board(8, 8, boardLayout, pieceLayout);
	//m_board->translateBoard(-4.0f, -5.0f, -15.0);

	//Game Manager
	m_gm = new GameManager();
	m_board->initGameManager(m_gm);

	//Attach Board to GameObject
	m_objBoard = new GameObject(m_board->transform.position, m_board->transform.scale, glm::vec4(m_board->transform.rotation, 1.0f));
	m_objBoard->attachModel(m_board);
	objectList.push_back(m_objBoard);

	//Text Renderer
	m_textRenderer = new TextRenderer();
	m_textRenderer->init("Resources/Fonts/Arkhip_font.ttf");

	return true;
}

void Scene_Main::processInput()
{
	/*
	//Camera movement with mouse
	m_camera->processMouse(EngineCore::getInstance()->getInputManager());
	//Camera movement with keys--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LSHIFT)) {
		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_w))
			m_camera->processKeyboard(FORWARD, m_deltaTime * 3.0f);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_s))
			m_camera->processKeyboard(BACKWARD, m_deltaTime * 3.0f);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_a))
			m_camera->processKeyboard(LEFT, m_deltaTime * 3.0f);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_d))
			m_camera->processKeyboard(RIGHT, m_deltaTime * 3.0f);
	}
	else {
		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_w))
			m_camera->processKeyboard(FORWARD, m_deltaTime);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_s))
			m_camera->processKeyboard(BACKWARD, m_deltaTime);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_a))
			m_camera->processKeyboard(LEFT, m_deltaTime);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_d))
			m_camera->processKeyboard(RIGHT, m_deltaTime);
	}
	//--
	*/

	//Moving the Selection of the Board--
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_RIGHT))
		m_board->moveHover(Board::MoveDirection::RIGHT);

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_LEFT))
		m_board->moveHover(Board::MoveDirection::LEFT);

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_UP))
		m_board->moveHover(Board::MoveDirection::UP);

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_DOWN))
		m_board->moveHover(Board::MoveDirection::DOWN);
	//--

	//Select
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_z))
		m_board->selectPiece();

	//Cancel
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_x))
		m_board->cancel();

	//End Turn
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_c))
		m_board->endTurn();

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	//Toggle Fullscreen
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_F1))
		EngineCore::getInstance()->getWindow()->toggleFullscreen();

	//Reset and Main Menu
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LSHIFT)) {
		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_q))
			EngineCore::getInstance()->gameInterface->loadScene(0);

		if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_r))
			EngineCore::getInstance()->gameInterface->loadScene(1);
	}

}

void Scene_Main::update(float deltaTime_)
{
	//Update the deltaTime for the processInput
	m_deltaTime = deltaTime_;

	//Update the framebuffer incase of screen size changes (Might not want to check every update, rather only check when screensize changes)
	framebuffer->updateFramebufferSize(EngineCore::getInstance()->getWindow());

	m_textRenderer->UpdateTextPosition(EngineCore::getInstance()->getWindow(), m_board->getHUD());

	m_gm->update(deltaTime_, m_camera);
	m_board->update(deltaTime_);
}

void Scene_Main::prerender()
{
	//Bind to the framebuffer and draw a scene as we normally would to colour texture; Must be called at the start of render
	framebuffer->bindBuffer();

	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();
}

void Scene_Main::render()
{
	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	m_renderer->render(m_camera, m_shaderBoard, objectList, lightList);
	m_renderer->renderParticles(m_camera, m_shaderParticles, m_gm->m_emitter, lightList);
	m_renderer->renderSkybox(m_camera, skybox);
}

void Scene_Main::postrender()
{
	//Must render the framebuffer last
	m_renderer->renderFramebuffer(m_shaderFramebuffer, framebuffer);

	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void Scene_Main::draw()
{
	m_textRenderer->RenderText(EngineCore::getInstance()->getWindow(), ShaderManager::getInstance()->getShader("shader_text"), m_board->getHUD());
}