#include "DemoScene.h"

using namespace AEON_ENGINE;

DemoScene::DemoScene()
{
	//Empty
}

DemoScene::~DemoScene()
{
	delete m_renderer;
	m_renderer = nullptr;

	delete m_camera;
	m_camera = nullptr;

	delete m_shaderProgram;
	m_shaderProgram = nullptr;

	delete m_containerProgram;
	m_containerProgram = nullptr;

	delete m_skyboxProgram;
	m_skyboxProgram = nullptr;

	delete m_framebufferProgram;
	m_framebufferProgram = nullptr;

	delete testModel;
	testModel = nullptr;

	delete testModel2;
	testModel2 = nullptr;

	delete dirLight;
	dirLight = nullptr;

	delete skybox;
	skybox = nullptr;

	delete framebuffer;
	framebuffer = nullptr;
}

bool DemoScene::initialize()
{
	//Lock Mouse
	EngineCore::getInstance()->getWindow()->lockMouse();

	//Camera
	m_camera = new Camera();

	//Renderer
	m_renderer = new Renderer();

	//Shaders
	m_shaderProgram = new Shader("../AeonEngine/Engine/Graphics/Shaders/lightingShaderVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/lightingShaderFrag.glsl");
	m_containerProgram = new Shader("../AeonEngine/Engine/Graphics/Shaders/primitiveCubeVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/primitiveCubeFrag.glsl");
	m_skyboxProgram = new Shader("../AeonEngine/Engine/Graphics/Shaders/skyboxVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/skyboxFrag.glsl");
	m_framebufferProgram = new Shader("../AeonEngine/Engine/Graphics/Shaders/framebuffersVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/framebuffersFrag.glsl");
	m_instanceProgram = new Shader("../AeonEngine/Engine/Graphics/Shaders/instancingModelVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/lightingShaderFrag.glsl");

	//Models
	testModel = new PrimitiveModel(PRIM_TYPE_CUBE, glm::vec3(0.0f, 0.0f, 0.0f), "Resources/Textures/container.png", "Resources/Textures/container_specular.png");
	modelList.push_back(testModel);
	testModel2 = new Model(glm::vec3(1.5f, -2.5f, 0.0f), "Resources/Models/Nanosuit/nanosuit.obj");
	testModel2->scale(glm::vec3(0.25f, 0.25f, 0.25f));
	modelList.push_back(testModel2);

	//Lights
	pointLight = new Light(LIGHT_POINT, glm::vec3(0.0f, 0.0f, 2.0f), true);
	lightList.push_back(pointLight);
	pointLight2 = new Light(LIGHT_POINT, glm::vec3(3.0f, 0.0f, 0.0f), true);
	lightList.push_back(pointLight2);
	dirLight = new Light(LIGHT_DIRECTIONAL, glm::vec3(0.0f, 0.0f, 0.0f), false);
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
	skybox = new Skybox(skyboxFaces);

	//Framebuffer
	framebuffer = new Framebuffer(EngineCore::getInstance()->getWindow());

	return true;
}

void DemoScene::processInput()
{
	//Camera movement with mouse
	m_camera->processMouse(EngineCore::getInstance()->getInputManager());

	//Camera movement with keys--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, m_deltaTime);
	//--

	//Moving the cube test--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_x))
		testModel->translate(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_z))
		testModel->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
		pointLight->translate(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
		pointLight->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_UP))
		pointLight->translate(glm::vec3(0.0f, 2.5f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_DOWN))
		pointLight->translate(glm::vec3(-0.0f, -2.5f, 0.0f) * m_deltaTime);
	//--

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_F1))
		EngineCore::getInstance()->getWindow()->toggleFullscreen();
}

void DemoScene::update(float deltaTime_)
{
	//Update the deltaTime for the processInput
	m_deltaTime = deltaTime_;

	//Update the framebuffer incase of screen size changes (Might not want to check every update, rather only check when screensize changes)
	framebuffer->updateFramebufferSize(EngineCore::getInstance()->getWindow());

	//**Rotation needs to be reset in the model for it to work properly
	//Will need to look into a fix
	//testModel2->rotate(((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DemoScene::render()
{	
	//Bind to the framebuffer and draw a scene as we normally would to colour texture; Must be called at the start of render
	framebuffer->bindBuffer();

	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();

	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_shaderProgram, modelList, lightList);
	//m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_skyboxProgram, skybox);

	//Must render the framebuffer last
	m_renderer->render(EngineCore::getInstance()->getWindow(), m_framebufferProgram, framebuffer);

	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void DemoScene::draw()
{

}
