#include "Scene_Main.h"

using namespace AEON_ENGINE;

Scene_Main::Scene_Main()
{
	//Empty
}

Scene_Main::~Scene_Main()
{
	//Empty
}

bool Scene_Main::initialize()
{
	//Lock Mouse
	EngineCore::getInstance()->getWindow()->lockMouse();

	//Camera
	m_camera = new Camera();

	//Renderer
	m_renderer = new Renderer();

	//Shaders
	m_shaderBoard = ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/lightingShaderVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");
	m_shaderPieces = ShaderManager::getInstance()->addShader("shader_container", "Resources/Shaders/litPrimitiveVert.glsl", "Resources/Shaders/litPrimitiveFrag.glsl");
	m_shaderSkybox = ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");

	//Lights
	dirLight = new Light(LIGHT_DIRECTIONAL, false);
	lightList.push_back(dirLight);

	//Skybox
	skyboxFaces = {
		"Resources/Cubemaps/Sky/right.jpg",
		"Resources/Cubemaps/Sky/left.jpg",
		"Resources/Cubemaps/Sky/top.jpg",
		"Resources/Cubemaps/Sky/bottom.jpg",
		"Resources/Cubemaps/Sky/back.jpg",
		"Resources/Cubemaps/Sky/front.jpg"
	};
	skybox = new Skybox(skyboxFaces, m_shaderSkybox);

	//Framebuffer
	framebuffer = new Framebuffer(EngineCore::getInstance()->getWindow());

	//GameObjects

	//Board layout
	std::vector<char> boardLayout = {
		0, 0, 1, 0, 0, 0, 0, 0,
		0, 2, 0, 1, 0, 0, 1, 0,
		0, 0, 0, 2, 0, 3, 0, 0,
		0, 3, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 2,
		0, 0, 0, 0, 0, 0, 3, 0,
		2, 0, 3, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 2, 0
	};

	//Piece layout
	std::vector<char> pieceLayout = {
		0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 0, 0, 6,
		1, 0, 0, 0, 0, 0, 0, 4,
		1, 0, 0, 0, 0, 0, 0, 4,
		2, 0, 0, 0, 0, 0, 0, 5,
		2, 0, 0, 0, 0, 0, 0, 5,
		3, 0, 0, 0, 0, 0, 0, 6,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	m_board = new Board(8, 8, boardLayout, pieceLayout);
	m_board->translateBoard(-4.0f, -5.0f, -15.0);

	m_objBoard = new GameObject(m_board->transform.position, m_board->transform.scale, glm::vec4(m_board->transform.rotation, 1.0f));
	m_objBoard->attachModel(m_board);
	objectList.push_back(m_objBoard);

	return true;
}

void Scene_Main::processInput()
{
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
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_RETURN))
		m_board->selectPiece();

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	//Toggle Fullscreen
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_F1))
		EngineCore::getInstance()->getWindow()->toggleFullscreen();
}

void Scene_Main::update(float deltaTime_)
{
	//Update the deltaTime for the processInput
	m_deltaTime = deltaTime_;

	//Update the framebuffer incase of screen size changes (Might not want to check every update, rather only check when screensize changes)
	framebuffer->updateFramebufferSize(EngineCore::getInstance()->getWindow());

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

}
