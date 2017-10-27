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

	delete pointLight;
	pointLight = nullptr;

	delete skybox;
	skybox = nullptr;
}

bool DemoScene::initialize()
{
	//**Lock Mouse
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_CaptureMouse(SDL_TRUE);

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
	pointLight = new Light(AEON_ENGINE::Light::LightType::POINT, glm::vec3(0.0f, 0.0f, 2.0f), true);
	modelList.push_back(pointLight);

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

void DemoScene::update()
{
	//**Maybe create a proper method for JUST processing inputs
	//**Deltatime
	//**Might need a different location for processing input
	//		- It checks what keycode was used from the inputmanager that's updating in the EngineCore class
	//		- How will individual objects track their inputs?
	//		- Should the camera be processed here in the scene as well? or in the Game/EngineCore class

	//**Makeshift Timestep -- Will need to create a proper class for it later
	float currentFrame = SDL_GetTicks() / 1000.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, deltaTime);

	//Moving the cube test--
	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_RIGHT))
		pointLight->translate(glm::vec3(2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_LEFT))
		pointLight->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_UP))
		pointLight->translate(glm::vec3(0.0f, 2.5f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_DOWN))
		pointLight->translate(glm::vec3(-0.0f, -2.5f, 0.0f) * deltaTime);
	//--

	if (EngineCore::getInstance()->getInputManager().wasMouseMoved()) {
		//**Might want to calculate mouse offset in the input manager or camera
		//Prevents screen from jumping to your mouses initial local
		if (firstMouse) {
			lastX = EngineCore::getInstance()->getInputManager().getMouseCoordsX();
			lastY = EngineCore::getInstance()->getInputManager().getMouseCoordsY();
			firstMouse = false;
		}

		float xoffset = EngineCore::getInstance()->getInputManager().getMouseCoordsX() - lastX;
		float yoffset = lastY - EngineCore::getInstance()->getInputManager().getMouseCoordsY(); //Reversed since y-coords range from bottom to top
		lastX = EngineCore::getInstance()->getInputManager().getMouseCoordsX();
		lastY = EngineCore::getInstance()->getInputManager().getMouseCoordsY();

		m_camera->processMouseMovement(xoffset, yoffset);
	}

	//Makeshift toggle for capturing the mouse (Change later) ---
	if (EngineCore::getInstance()->getInputManager().isKeyPressed(SDLK_ESCAPE)) {
		if (captureMouse)
			captureMouse = false;
		else
			captureMouse = true;
	}

	if (captureMouse) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_CaptureMouse(SDL_TRUE);
	}
	if (!captureMouse) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_CaptureMouse(SDL_FALSE);
	}
	//---
}

void DemoScene::render()
{	
	//**Must be outside the renderer to prevent stuttering when making multiple render calls
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	////Hardcoded Lighting for TESTING
	//m_shaderProgram->use();
	//m_shaderProgram->setVec3("light.position", lightPos);
	//m_shaderProgram->setVec3("viewPos", m_camera->getPos());

	////Light properties
	//m_shaderProgram->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	//m_shaderProgram->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	//m_shaderProgram->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	////Material properties
	//m_shaderProgram->setFloat("shininess", 64.0f);

	//Renderer
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_shaderProgram, modelList);
	//m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_skyboxProgram, skybox);

	//HARDCODE MODEL LOADING HERE TO TEST ASSIMP
	//Rendering
	//m_shaderProgram->use();
	//m_shaderProgram->setMat4("view", m_camera->getView());
	//m_shaderProgram->setMat4("projection", m_camera->getProj());
	//glm::mat4 model = glm::mat4();
	//model *= glm::translate(model, glm::vec3(1.5f, -2.5f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	//m_shaderProgram->setMat4("model", model);
	//testModel2->render(m_shaderProgram);

	//m_shaderProgram->use();
	//m_shaderProgram->setMat4("view", m_camera->getView());
	//m_shaderProgram->setMat4("projection", m_camera->getProj());
	//testModel->render(m_shaderProgram);

	//Rotation needs to be reset in the model for it to work properly
	//Will need to look into a fix
	//testModel2->rotate(((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//**Must be outside the renderer to prevent stuttering when making multiple render calls
	EngineCore::getInstance()->getWindow()->swapBuffers();
}

void DemoScene::draw()
{

}
