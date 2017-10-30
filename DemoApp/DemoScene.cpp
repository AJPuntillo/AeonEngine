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

	delete testModel;
	testModel = nullptr;

	delete testModel2;
	testModel2 = nullptr;

	delete spotLight;
	spotLight = nullptr;

	delete skybox;
	skybox = nullptr;
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

	//Models
	testModel = new PrimitiveModel(glm::vec3(0.0f, 0.0f, 0.0f), "Resources/Textures/container.png", "Resources/Textures/container_specular.png");
	modelList.push_back(testModel);
	testModel2 = new Model(glm::vec3(1.5f, -2.5f, 0.0f), "Resources/Models/Nanosuit/nanosuit.obj");
	testModel2->scale(glm::vec3(0.25f, 0.25f, 0.25f));
	modelList.push_back(testModel2);

	//Lights
	//pointLight = new Light(AEON_ENGINE::Light::LightType::POINT, glm::vec3(0.0f, 0.0f, 2.0f), true);
	//lightList.push_back(pointLight);
	spotLight = new Light(AEON_ENGINE::Light::LightType::DIRECTIONAL, glm::vec3(0.0f, 0.0f, 0.0f), false);
	lightList.push_back(spotLight);

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

	return true;
}

void DemoScene::processInput()
{
	//**Makeshift Timestep -- Will need to create a proper class for it later
	float currentFrame = SDL_GetTicks() / 1000.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//Camera movement with mouse
	m_camera->processMouse(EngineCore::getInstance()->getInputManager());

	//Camera movement with keys--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, deltaTime);
	//--

	//Moving the cube test--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
		pointLight->translate(glm::vec3(2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
		pointLight->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_UP))
		pointLight->translate(glm::vec3(0.0f, 2.5f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_DOWN))
		pointLight->translate(glm::vec3(-0.0f, -2.5f, 0.0f) * deltaTime);
	//--

	//Unlock Mouse
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->unlockMouse();
}

void DemoScene::update()
{
	//**Rotation needs to be reset in the model for it to work properly
	//Will need to look into a fix
	//testModel2->rotate(((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DemoScene::render()
{	
	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();

	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_shaderProgram, modelList, lightList);
	//m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_skyboxProgram, skybox);

	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void DemoScene::draw()
{

}
