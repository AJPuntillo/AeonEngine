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
	EngineCore::getInstance()->getWindow()->lockMouse();

	//Initialize all your pointer objects
	//All pointer objects must be initialized using a 'new'... but remember the 'new' rule mentioned above

	//Camera
	m_camera = new Camera();

	//Renderer
	m_renderer = new Renderer();

	//Shaders
	//Shaders must be intialized with two string paths, first path to the Vertex Shader and the second to the Fragment Shader
	//If you decide to create your own shaders, make sure the location you provide is the correct path it is located in
	//Shaders have been changed to use the Shader Manager which is a singleton, so instead of using Shaders for render calls, we use ShaderHandles
	m_shaderModel		= ShaderManager::getInstance()->addShader("shader_lighting", "Resources/Shaders/modelShaderVert.glsl", "Resources/Shaders/modelShaderFrag.glsl");
	m_shaderContainer	= ShaderManager::getInstance()->addShader("shader_container", "Resources/Shaders/litPrimitiveVert.glsl", "Resources/Shaders/litPrimitiveFrag.glsl");
	m_shaderLamp		= ShaderManager::getInstance()->addShader("shader_lamp", "Resources/Shaders/lampVert.glsl", "Resources/Shaders/lampFrag.glsl");
	m_shaderSkybox		= ShaderManager::getInstance()->addShader("shader_skybox", "Resources/Shaders/skyboxVert.glsl", "Resources/Shaders/skyboxFrag.glsl");
	m_shaderFramebuffer = ShaderManager::getInstance()->addShader("shader_framebuffer", "Resources/Shaders/framebuffersVert.glsl", "Resources/Shaders/framebuffersFrag.glsl");

	//***OUTDATED***
	//*USE GAMEOBJECTS NOW

	//Models
	//Models and PrimitiveModels inherit from a base class called 'Entity' (pure virtual)
	//Entity contains a position vector along with transformation matrices (model, translation, scale, and rotation matrices)
	//It also contains basic methods to translate, rotate, and scale the entity
	//So this means that all objects inherited from this class (Model and PrimitiveModel) also have these variables and methods stored within them

	//PrimitiveModels have a few overloaded constructors, they can be loaded with a position and a texture.. or not
	//I would check out the class to see your options on intialize them
	//I am providing the contructor with a Vec3 that will serve as the container's position, and a path the texture I want to load
	//m_modelContainer = new PrimitiveModel(PrimitiveMesh::PrimitiveType::CUBE, glm::vec3(0.0f, 0.0f, 0.0f), "Resources/Textures/container.png");
	//Now we push the newly intialized model into the model list we created in the header file
	//Because they are pure virtual, they are able to be pushed into a list of type 'Entity'
	//m_modelList.push_back(m_modelContainer);

	//Here I am repeated the steps as above for the Model, but this time I need to provde the location to the '.obj' file so that ASSIMP knows what model to load
	//I am also using one of the inherited methods to scale down the model because it is rather large
	//Again, I advise you check out the Entity and Model .h/.cpp files to see all that that can do.
	//But to put it briefly, all models/primitivemodels can translate, rotate, and scale.
	//So if you want to spawn a model upsidedown or facing another way, you can set their orientation here when you initialize them
	//m_modelNanosuit = new Model(glm::vec3(1.5f, -1.5f, 0.0f), "Resources/Models/Nanosuit/nanosuit.obj");
	//m_modelNanosuit->scale(glm::vec3(0.15f, 0.15f, 0.15f));
	//m_modelList.push_back(m_modelNanosuit); //Notice I pushed both the container and the nanosuit model into the same list even though they are different object types (PrimitiveModel and Model)? Inheritance is a blessing..

	//***

	//Gameobjects are now the way to go
	//Like the Model and PrimitiveModel class, Gameobjects inherit from Entity. But now only Gameobjects contain Transforms, which hold their model matrix
	//The reason for having a Gameobject class is similar for Unity having a Gameobject class. We can now choose to put different components on the objects
	//So if we want our Gameobject to contain a model, it can. If we want object to also contain a BoundingVolume, it can. It just adds more flexibility to our Engine
	//To create a Gameobject, you must initialize it with a either a path to a .obj file (Which creates and attaches a model to it) or give it a PrimitiveMesh type (Which creates and attachs a PrimitiveModel to it)
	m_modelContainer = new GameObject(PrimitiveMesh::PrimitiveMesh::CUBE);
	m_containerList.push_back(m_modelContainer);

	m_modelNanosuit = new GameObject("Resources/Models/Nanosuit/nanosuit.obj");
	//Instead of accessing the model's translate/scale methods, they have no been moved to the Transform class (which every Gameobject contains) **Similar to Unity, if you want to move, scale, rotate an object then call the object's transform
	m_modelNanosuit->transform.translateBy(-2.0f, -2.5f, 0.0f);
	m_modelNanosuit->transform.scaleBy(0.25f, 0.25f, 0.25f);
	m_modelList.push_back(m_modelNanosuit);

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
	//Skybox now needs a ShaderHandle to know which shader it is going to be rendered with
	m_skybox = new Skybox(m_skyboxFaces, m_shaderSkybox);

	return true;
}

void TutorialScene::processInput()
{
	//**Makeshift Timestep -- Will need to create a proper class for it later
	float currentFrame = SDL_GetTicks() / 1000.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//Camera movement with mouse
	//This is for calculating offset of the camera, so that you can look around with the camera using your mouse
	m_camera->processMouse(EngineCore::getInstance()->getInputManager());

	//This is tracking input, the camera moves with W, A, S, D
	//Later on this will be implemented in its own method, but for testing purposes this will do just fine
	//You can add more keys to be tracks by copying and pasting the if statement and changing the key to be pressed
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, deltaTime);

	//When the left/right key is pressed, called the model's translate method and move it by 2.5units * deltatime --
	//This is for testing movement of models
	//Feel free to play around with these controls for your own testing
	//**Remember that we are accessing the object's transform now to make transformations
	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_RIGHT))
		m_modelContainer->transform.translateBy(glm::vec3(2.5f, 0.0f, 0.0f) * deltaTime);

	if (EngineCore::getInstance()->getInputManager()->isKeyDown(SDLK_LEFT))
		m_modelContainer->transform.translateBy(glm::vec3(-2.5f, 0.0f, 0.0f) * deltaTime);

	//Toggle Mouse Capture
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_ESCAPE))
		EngineCore::getInstance()->getWindow()->toggleMouseCapture();

	//Fullscreen
	if (EngineCore::getInstance()->getInputManager()->isKeyPressed(SDLK_F1))
		EngineCore::getInstance()->getWindow()->toggleFullscreen();
}

void TutorialScene::update(float deltaTime_)
{
	//Update stuff...
}

void TutorialScene::prerender()
{
	//Clear buffers (and clear the background colour); Must be before render is called
	m_renderer->clearBuffers();
}

void TutorialScene::render()
{
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
	//The vector of models (Gameobjects) is to know which objects to render with the previously linked shader
	m_renderer->render(m_camera, m_shaderModel, m_modelList);
	m_renderer->render(m_camera, m_shaderLamp, m_containerList); //Because we want to render the container with a different shader, we make a new render call with a different shader handle and object list
	m_renderer->renderSkybox(m_camera, m_skybox);
}

void TutorialScene::postrender()
{
	//Swap buffers for double buffering; Must be after render is called
	m_renderer->swapBuffers(EngineCore::getInstance()->getWindow());
}

void TutorialScene::draw()
{
	//Draw 2D stuff!
}