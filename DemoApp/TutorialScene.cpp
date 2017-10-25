#include "TutorialScene.h"

using namespace AEON_ENGINE; //Use the namespace! Or else you will not have access to anything Engine related

TutorialScene::TutorialScene()
{
	//Empty
	//We take care of everything in the 'initialize' method
}

TutorialScene::~TutorialScene()
{
	//So pointers are great, right?
	//They are.. but here's the thing:
	//When you create a pointer, it allocates it to the STACK and therefore does not get deleted after ever loop.
	//That means if you make too many and do not manage them, you are eating up loads of memory.
	//***A good rule of thumb: For every 'new' keyword, there needs to be a 'delete' to match it.

	//Camera
	delete m_camera;
	m_camera = nullptr; //I set it back to null by default, may not be needed
	//Shaders
	delete m_modelShader;
	m_modelShader = nullptr;
	delete m_skyboxShader;
	m_skyboxShader = nullptr;
	//Renderer
	delete m_renderer;
	m_renderer = nullptr;
	//Models
	delete m_modelContainer;
	m_modelContainer = nullptr;
	delete m_modelNanosuit;
	m_modelNanosuit = nullptr;
	//Skybox
	delete m_skybox;
	m_skybox = nullptr;
}

bool TutorialScene::initialize()
{
	//This locks ad captures the mouse
	//If you want to see your cursor then comment out these two lines
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);

	//Initialize all your pointer objects
	//All pointer objects must be initialized using a 'new'... but remember the 'new' rule mentioned above

	//Camera
	m_camera = new Camera();

	//Renderer
	m_renderer = new Renderer();

	//Shaders
	//Shaders must be intialized with two string paths, first path to the Vertex Shader and the second to the Fragment Shader
	//If you decide to create your own shaders, make sure the location you provide is the correct path it is located in
	m_modelShader = new Shader("../AeonEngine/Engine/Graphics/Shaders/vertShaderTest.glsl", "../AeonEngine/Engine/Graphics/Shaders/fragShaderTest.glsl");
	m_skyboxShader = new Shader("../AeonEngine/Engine/Graphics/Shaders/skyboxVert.glsl", "../AeonEngine/Engine/Graphics/Shaders/skyboxFrag.glsl");

	//Models
	//Models and PrimitiveModels inherit from a base class called 'Entity' (pure virtual)
	//Entity contains a position vector along with transformation matrices (model, translation, scale, and rotation matrices)
	//It also contains basic methods to translate, rotate, and scale the entity
	//So this means that all objects inherited from this class (Model and PrimitiveModel) also have these variables and methods stored within them

	//PrimitiveModels have a few overloaded constructors, they can be loaded with a position and a texture.. or not
	//I would check out the class to see your options on intialize them
	//I am providing the contructor with a Vec3 that will serve as the container's position, and a path the texture I want to load
	m_modelContainer = new PrimitiveModel(glm::vec3(0.0f, 0.0f, 0.0f), "Resources/Textures/container.png");
	//Now we push the newly intialized model into the model list we created in the header file
	//Because they are pure virtual, they are able to be pushed into a list of type 'Entity'
	m_modelList.push_back(m_modelContainer);

	//Here I am repeated the steps as above for the Model, but this time I need to provde the location to the '.obj' file so that ASSIMP knows what model to load
	//I am also using one of the inherited methods to scale down the model because it is rather large
	//Again, I advise you check out the Entity and Model .h/.cpp files to see all that that can do.
	//But to put it briefly, all models/primitivemodels can translate, rotate, and scale.
	//So if you want to spawn a model upsidedown or facing another way, you can set their orientation here when you initialize them
	m_modelNanosuit = new Model(glm::vec3(1.5f, -1.5f, 0.0f), "Resources/Models/Nanosuit/nanosuit.obj");
	m_modelNanosuit->scale(glm::vec3(0.15f, 0.15f, 0.15f));
	m_modelList.push_back(m_modelNanosuit); //Notice I pushed both the container and the nanosuit model into the same list even though they are different object types (PrimitiveModel and Model)? Inheritance is a blessing..

	//Skybox
	//Providing the location to all 6 faces needed for a cubemap/skybox
	//***You must load the faces into the vector before you intialize the Skybox object because it takes in the vector in it's constructor
	m_skyboxFaces = {
		"Resources/Cubemaps/Sky/right.jpg",
		"Resources/Cubemaps/Sky/left.jpg",
		"Resources/Cubemaps/Sky/top.jpg",
		"Resources/Cubemaps/Sky/bottom.jpg",
		"Resources/Cubemaps/Sky/back.jpg",
		"Resources/Cubemaps/Sky/front.jpg"
	};
	m_skybox = new Skybox(m_skyboxFaces);

	return true;
}

void TutorialScene::update()
{
	//**Makeshift Timestep -- Will need to create a proper class for it later
	float currentFrame = SDL_GetTicks() / 1000.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//This is tracking input, the camera moves with W, A, S, D
	//Later on this will be implemented in its own method, but for testing purposes this will do just fine
	//You can add more keys to be tracks by copying and pasting the if statement and changing the key to be pressed
	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, deltaTime);

	//When the left/right key is pressed, called the model's translate method and move it by 2.5units * deltatime --
	//This is for testing movement of models
	//Feel free to play around with these controls for your own testing
	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_RIGHT))
		m_modelContainer->translate(glm::vec3(2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager().isKeyDown(SDLK_LEFT))
		m_modelContainer->translate(glm::vec3(-2.5f, 0.0f, 0.0f) * deltaTime);
	//--

	//***This is for calculating offset of the camera, so that you can look around with the camera using your mouse
	//This will also be moved with the rest of the input to a more cleanerer method, but this works perfectly right now for testing
	//No need to alter this.
	if (EngineCore::getInstance()->getInputManager().wasMouseMoved()) {
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
}

void TutorialScene::render()
{
	//**Must be outside the renderer to prevent stuttering when making multiple render calls
	//ClearColor is the background colour of the window
	//Clear are the buffers to be cleared (Best to leave these as is)
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Initialize/update View and Projection matrices
	//The camera contains both the view and projection matrix for rendering
	//Create and update these two matrices before you make a call to the Renderer
	m_camera->createViewMatrix();
	m_camera->createProjectionMatrix(EngineCore::getInstance()->getWindow()->getScreenWidth(), EngineCore::getInstance()->getWindow()->getScreenHeight());

	//Renderer
	//The Renderer is where all the magic is
	//The Renderer has a method called 'render' that takes in 4 parameters:
	//The camera to access the view and projection matrix
	//The window to access the 'swapBuffers' to use double buffering (Right now that methos is outside the Renderer, so this parameter may be removed later)
	//The shader that will be used to render the objects
	//The vector of models (Entity's) to know which objects to render with the previously linked shader
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_modelShader, m_modelList);
	m_renderer->render(m_camera, EngineCore::getInstance()->getWindow(), m_skyboxShader, m_skybox); //The 'render' method is overloaded to take in a skybox instead of a list of Entity's

	//**Must be outside the renderer to prevent stuttering when making multiple render calls
	//Allows for double buffering
	EngineCore::getInstance()->getWindow()->swapBuffers();
}

void TutorialScene::draw()
{
	//Draw 2D stuff!
}