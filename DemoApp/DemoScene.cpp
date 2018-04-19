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
	m_shaderLighting    = ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/lightingShaderVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");
	m_shaderParticles   = ShaderManager::getInstance()->addShader("shader_particles", "Resources/Shaders/simpleParticle_Vert.glsl", "Resources/Shaders/simpleParticle_Frag.glsl");
	m_shaderContainer	= ShaderManager::getInstance()->addShader("shader_container", "Resources/Shaders/litPrimitiveVert.glsl", "Resources/Shaders/litPrimitiveFrag.glsl");
	m_shaderLamp		= ShaderManager::getInstance()->addShader("shader_lamp", "Resources/Shaders/lampVert.glsl", "Resources/Shaders/lampFrag.glsl");
	m_shaderSkybox		= ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");
	m_shaderInstancing	= ShaderManager::getInstance()->addShader("shader_instance", "Resources/Shaders/instancingModelVert.glsl", "Resources/Shaders/lightingShaderFrag.glsl");

	//GameObjects
	model_nanosuit = new GameObject("Resources/Models/Nanosuit/nanosuit.obj");
	model_nanosuit->transform.translateBy(0.0f, 0.0f, 0.0f);
	model_nanosuit->transform.scaleBy(0.25f, 0.25f, 0.25f);
	model_nanosuit->setupVolume();
	//objectList.push_back(model_nanosuit);
	//Testing the bounding volume values of the model
	//std::cout << model_nanosuit->boundingVolume->getMaxCorner().x << " " << model_nanosuit->boundingVolume->getMaxCorner().y << " " << model_nanosuit->boundingVolume->getMaxCorner().z << std::endl;
	//std::cout << model_nanosuit->boundingVolume->getMinCorner().x << " " << model_nanosuit->boundingVolume->getMinCorner().y << " " << model_nanosuit->boundingVolume->getMinCorner().z << std::endl;

	model_cube = new GameObject(Mesh::PrimitiveType::CUBE);
	//model_cube->transform.translateBy(1.0f, 0.0f, 0.0f);
	//model_cube->transform.translateBy(0.0, -0.3f, 0.0f);
	//model_cube->transform.scaleBy(15.0f, 0.3f, 15.0f);
	model_cube->transform.rotateBy(45.0f, 0.0f, 1.0f, 0.0f);
	model_cube->transform.translateBy(0.0, 2.5f, 0.0f);
	objectList2.push_back(model_cube);

	//Lights
	pointLight = new Light(LIGHT_POINT, true);
	pointLight->transform.translateBy(1.0f, 2.5f, 1.0f);
	pointLight->setLightIntensity(glm::vec3(0.05f, 0.05f, 0.8f), glm::vec3(0.2f, 0.2f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
	lightList.push_back(pointLight);

	pointLight2 = new Light(LIGHT_POINT, true);
	pointLight2->transform.translateBy(-1.0f, 2.5f, -1.0f);
	pointLight2->setLightIntensity(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	lightList.push_back(pointLight2);

	pointLight3 = new Light(LIGHT_POINT, true);
	pointLight3->transform.translateBy(-1.0f, 2.5f, 1.0f);
	//pointLight3->setLightIntensity(glm::vec3(0.8f, 0.05f, 0.05f), glm::vec3(0.8f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f));
	lightList.push_back(pointLight3);

	pointLight4 = new Light(LIGHT_POINT, true);
	pointLight4->transform.translateBy(1.0f, 2.5f, -1.0f);
	pointLight4->setLightIntensity(glm::vec3(0.05f, 0.8f, 0.05f), glm::vec3(0.2f, 0.8f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f));
	lightList.push_back(pointLight4);

	dirLight = new Light(LIGHT_DIRECTIONAL, false);
	lightList.push_back(dirLight);

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

	//board = new Board(8, 8, boardLayout, pieceLayout);
	//board->translateBoard(-4.0f, -5.0f, -15.0);

	//std::cout << "CENTER POS AFTER" << board->getBoard()[2]->m_centerPos.x << " " << board->getBoard()[2]->m_centerPos.y << " " << board->getBoard()[2]->m_centerPos.z << std::endl;
	//std::cout << board->getAdjacentTiles(board->getBoard()[2]).size() << std::endl;

	//for (auto edge : board->getBoard()[1]->m_edges) {
	//	std::cout << "EDGE:" << edge.connectedTo->m_centerPos.x << " " << edge.connectedTo->m_centerPos.y << " " << edge.connectedTo->m_centerPos.z << std::endl;
	//}


	//Particles
	emitter = new ParticleEmitter(10, 3.0f);
	emitter->setLooping(true);
	emitter->play();
	//particleObject = new GameObject(100, 3.0f);
	//objectList.push_back(particleObject);

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
		pointLight->transform.translateBy(glm::vec3(0.0f, -2.5f, 0.0f) * m_deltaTime);
	//--

	////Moving the model--
	//if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
	//	model_nanosuit->transform.translateBy(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	//if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
	//	model_nanosuit->transform.translateBy(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	//if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_UP))
	//	model_nanosuit->transform.translateBy(glm::vec3(0.0f, 2.5f, 0.0f) * m_deltaTime);

	//if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_DOWN))
	//	model_nanosuit->transform.translateBy(glm::vec3(-0.0f, -2.5f, 0.0f) * m_deltaTime);
	////--

	//Moving the Selection of the Board--
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
		pointLight2->transform.translateBy(glm::vec3(2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
		pointLight2->transform.translateBy(glm::vec3(-2.5f, 0.0f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_UP))
		pointLight2->transform.translateBy(glm::vec3(0.0f, 2.5f, 0.0f) * m_deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_DOWN))
		pointLight2->transform.translateBy(glm::vec3(0.0f, -2.5f, 0.0f) * m_deltaTime);

	//Select
	//if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_RETURN))
	//	board->selectPiece();

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

	//board->update(deltaTime_);

	emitter->update(deltaTime_);
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
	//m_renderer->render(m_camera, m_shaderLighting, board, lightList);
	//m_renderer->render(m_camera, m_shaderLighting, piece, lightList);
	m_renderer->render(m_camera, m_shaderLighting, objectList, lightList);
	m_renderer->renderParticles(m_camera, m_shaderParticles, emitter, lightList);
	m_renderer->render(m_camera, m_shaderContainer, objectList2, lightList);
	m_renderer->renderLightMeshes(m_camera, m_shaderLamp, lightList);
	//m_renderer->renderSkybox(m_camera, skybox);
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
