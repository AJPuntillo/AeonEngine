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
	m_shaderLighting	= ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/lightingShaderVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");
	m_shaderContainer	= ShaderManager::getInstance()->addShader("shader_container", "Resources/Shaders/litPrimitiveVert.glsl", "Resources/Shaders/litPrimitiveFrag.glsl");
	m_shaderLamp		= ShaderManager::getInstance()->addShader("shader_lamp", "Resources/Shaders/lampVert.glsl", "Resources/Shaders/lampFrag.glsl");
	m_shaderSkybox		= ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");
	m_shaderInstancing	= ShaderManager::getInstance()->addShader("shader_instance", "Resources/Shaders/instancingModelVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");

	//GameObjects
	model_nanosuit = new GameObject("Resources/Models/Nanosuit/nanosuit.obj");
	model_nanosuit->transform.translateBy(-1.0f, -2.5f, 0.0f);
	model_nanosuit->transform.scaleBy(0.25f, 0.25f, 0.25f);
	objectList.push_back(model_nanosuit);

	model_cube = new GameObject(PrimitiveMesh::PrimitiveMesh::CUBE);
	model_cube->transform.translateBy(1.0f, 0.0f, 0.0f);
	objectList2.push_back(model_cube);

	//Lights
	pointLight = new Light(LIGHT_POINT, true);
	pointLight->transform.translateBy(0.0f, 0.0f, 2.0f);
	lightList.push_back(pointLight);

	pointLight2 = new Light(LIGHT_POINT, true);
	pointLight2->transform.translateBy(3.0f, 0.0f, 0.0f);
	lightList.push_back(pointLight2);

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

	return true;
}

void DemoScene::processInput()
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

	//Moving a light--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_l))
		pointLight->transform.translateBy(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_j))
		pointLight->transform.translateBy(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_i))
		pointLight->transform.translateBy(glm::vec3(0.0f, 2.5f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_k))
		pointLight->transform.translateBy(glm::vec3(-0.0f, -2.5f, 0.0f) * m_deltaTime);
	//--

	//Moving the model--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
		model_nanosuit->transform.translateBy(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
		model_nanosuit->transform.translateBy(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_UP))
		model_nanosuit->transform.translateBy(glm::vec3(0.0f, 2.5f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_DOWN))
		model_nanosuit->transform.translateBy(glm::vec3(-0.0f, -2.5f, 0.0f) * m_deltaTime);
	//--

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	//Toggle Fullscreen
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
	//model_nanosuit->transform.rotateBy((((float)SDL_GetTicks() / 1000) * glm::radians(50.0f)), 0.0f, 1.0f, 0.0f);
}

void DemoScene::prerender()
{
	//Bind to the framebuffer and draw a scene as we normally would to colour texture; Must be called at the start of render
	framebuffer->bindBuffer();

	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();
}

void DemoScene::render()
{	
	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());
	
	//Renderer
	//m_renderer->render(m_camera, m_shaderLighting, objectList, lightList);
	m_renderer->render(m_camera, m_shaderContainer, objectList2, lightList);
	m_renderer->renderLightMeshes(m_camera, m_shaderLamp, lightList);
	m_renderer->renderSkybox(m_camera, skybox);
}

void DemoScene::postrender()
{
	//Must render the framebuffer last
	m_renderer->renderFramebuffer(m_shaderFramebuffer, framebuffer);

	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void DemoScene::draw()
{

}
