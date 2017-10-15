#include "DemoScene.h"

using namespace AEON_ENGINE;

//**FIX FOR LATER
float lastX = 800 / 2; //Center of screen x
float lastY = 600 / 2; //Center of screen y
bool firstMouse = true;
//Timing
float deltaTime = 0.0f; //Time between current frame and last frame
float lastFrame = 0.0f; //Time of last frame

DemoScene::DemoScene()
{
	//Empty
}

DemoScene::~DemoScene()
{
	delete m_renderer;
	m_renderer = nullptr;

	delete m_shaderProgram;
	m_shaderProgram = nullptr;

	delete testModel;
	testModel = nullptr;

	delete m_camera;
	m_camera = nullptr;
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
	m_shaderProgram = new Shader("C:/Users/Andrew/Documents/Projects/C++ Projects/AeonEngine/AeonEngine/Engine/Graphics/Shaders/vertShaderTest.glsl", "C:/Users/Andrew/Documents/Projects/C++ Projects/AeonEngine/AeonEngine/Engine/Graphics/Shaders/fragShaderTest.glsl");

	//Meshes
	testModel = new Model(glm::vec3(0.0f, 0.0f, 0.0f));
	testModel->loadMesh();

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
	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_g))
		testModel->translate(glm::vec3(2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_f))
		testModel->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * deltaTime);
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

	//Makeshift toggle for capturing the mouse (Change later)
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
}

void DemoScene::render()
{	
	//Initialize/update View and Projection matrices
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_shaderProgram, testModel); //Change to take in a vector of models
	testModel->rotate(((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

void DemoScene::draw()
{

}
