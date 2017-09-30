#include "DemoScene.h"

using namespace AEON_ENGINE;

//**FIX FOR LATER
float lastX = 800 / 2; //Center of screen x
float lastY = 600 / 2; //Center of screen y
bool firstMouse = true;
//Timing
float deltaTime = 0.0f; //Time between current frame and last frame
float lastFrame = 0.0f; //Time of last frame

//Vertex structure
float vertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};

DemoScene::DemoScene()
{
	//Empty
}

DemoScene::~DemoScene()
{
	//Empty
}

bool DemoScene::initialize()
{
	//**Lock Mouse
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		camera.processKeyboard(FORWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_s))
		camera.processKeyboard(BACKWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_a))
		camera.processKeyboard(LEFT, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_d))
		camera.processKeyboard(RIGHT, deltaTime);

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

		camera.processMouseMovement(xoffset, yoffset);
	}
}

void DemoScene::render()
{
	//**Store shader/window variables -- for convenience
	GLuint shaderID = EngineCore::getInstance()->getShader()->getShaderProgram();
	int SCREEN_WIDTH = EngineCore::getInstance()->getWindow()->getScreenWidth();
	int SCREEN_HEIGHT = EngineCore::getInstance()->getWindow()->getScreenHeight();

	//Rendering
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Draw our first triangle
	EngineCore::getInstance()->getShader()->use();
	
	//Create transformations
	glm::mat4 model;
	glm::mat4 view = camera.createViewMatrix();
	glm::mat4 projection = glm::perspective(camera.getFOV(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	model = glm::rotate(model, ((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	EngineCore::getInstance()->getShader()->setMat4("model", model);
	EngineCore::getInstance()->getShader()->setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	EngineCore::getInstance()->getShader()->setMat4("projection", projection);

	// render container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	//Swap buffers
	EngineCore::getInstance()->getWindow()->swapBuffers();
}

void DemoScene::draw()
{

}
