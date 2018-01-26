//Andrew Puntillo

//***
/*
	--QUICK DESCRIPTION--

	The Scene is where it all happens. This is where you control what and how everything is displayed in the window.
	This will be the most important class to understand in the engine because this is going to be your "testbed" to
	test all your work.

	But first I will briefly explain how the engine starts up and gets to know the scene.

	Every game needs a 'main.cpp'. In the main, it makes a call to the Engine's 'EngineCore' class.
	This class is a singleton and contains the bulk of the engine. It is responsible for setting up the window,
	opengl, and sdl. It also contains the gameloop. The EngineCore makes calls to update, render, and draw. (We'll refer to them as the 'core' methods).
	But when it calls those methods, it's really calling the "Game"'s version of those methods.

	The EngineCore needs a "Game", so in our case our's is 'DemoGame'.
	'DemoGame' inherits from a abstract class in the Engine called 'GameInterface'.
	The GameInterface/DemoGame acts as a "Scene Manager" of sorts. It is able to store multiple scenes (like this one)
	and is able to switch to any other scene you tell it to. It contains the update, render, and draw methods like mentioned above.
	When those core methods are called they really call the "Scene"'s core methods. And that is why the Scene is the most important.
	Whatever you render/update/draw in a scene, the Scene will pass it to the Game, which will pass it to the EngineCore.

	So based on above, that means a GameInterface needs atleast one "Scene" by default.
	a "Scene" class inherits from another abstract class in the Engine called 'SceneInterface'.
	In the scene, you want to include all the objects/headers files you need to make the scene of your dreams.

	When you create your own scene (or you can just use this one to play around in and test your stuff)
	you will need to go to 'DemoGame' and change out the default scene that gets loaded in the 'initialize' method.
*/
//***

#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

//Include all the headers you need
//You'll have to explore the Engine files to see whats available
//But I will be covering all the important/mandatory/working(lol) files in this tutorial scene

#include <AeonEngine/Engine/Core/SceneInterface.h>			//SceneInterface is needed to inherit from; explained above
#include <AeonEngine/Engine/Camera/Camera.h>				//Camera is important for displaying the scene; Can move around like a FPS camera; **CONTAINS VIEW AND PROJECTION MATRIX**
#include <AeonEngine/Engine/Rendering/3D/Renderer.h>		//Renderer is used to render your objects/models/skybox/etc
#include <AeonEngine/Engine/Rendering/3D/Model.h>			//Model uses ASSIMP to load more complex models (Like the Nanosuit/Miku) OR can load a primitive (Like a CUBE or PLANE)
#include <AeonEngine/Engine/Rendering/3D/Skybox.h>			//Skybox creates the a skybox... yeah
#include <AeonEngine/Engine/Rendering/3D/GameObject.h>		//Gameobjects are going to be the main focus of everything seen in a scene; They contain models, transforms, (and optionally shaders); Think of them like Unity GameObjects

class TutorialScene : public AEON_ENGINE::SceneInterface //Must inherit from the Engine's 'SceneInterface' as explained above
{
public:
	TutorialScene();
	//These methods are virtual because they are inherited from SceneInterface
	virtual ~TutorialScene();

	virtual bool initialize();						//Initializes the scene; used to setup objects; It returns bool for error checking
	virtual void processInput();					//Updates all input
	virtual void update(float deltaTime_);			//Update everything; good for physics, movement, input, etc..
	virtual void prerender();						//Handles Pre-render calls such as clearing the buffers
	virtual void render();							//Render everything to show up in the window
	virtual void postrender();						//Handles Post-render calls such as swapping buffers; Allows UI elements to not be left out of render calls
	virtual void draw();							//Draw will most likely be used to draw 2D elements, like UI

private:
	//***Notice that all objects are prefixed with 'AEON_ENGINE'
	//That is because that is the namespace all the engine objects are under
	//And we do not use the AEON_ENGINE namespace inside the .h file, but you will see it in the .cpp

	//Also, pointers are important.

	//Camera
	AEON_ENGINE::Camera* m_camera;
	//Shader Program
	AEON_ENGINE::ShaderManager::HandleType m_shaderModel;
	AEON_ENGINE::ShaderManager::HandleType m_shaderContainer;
	AEON_ENGINE::ShaderManager::HandleType m_shaderLamp;
	AEON_ENGINE::ShaderManager::HandleType m_shaderSkybox;
	AEON_ENGINE::ShaderManager::HandleType m_shaderFramebuffer;
	//Renderer
	AEON_ENGINE::Renderer* m_renderer;				//Takes in a list of objects to be rendered and a shader
	//Gameobjects
	AEON_ENGINE::GameObject* m_modelContainer;
	AEON_ENGINE::GameObject* m_modelNanosuit;
	//Skybox
	AEON_ENGINE::Skybox* m_skybox;
	std::vector<std::string> m_skyboxFaces;			//A skybox object needs a vector of path locations to the faces used in the skybox
	//Model Lists
	std::vector<AEON_ENGINE::GameObject*> m_modelList;	//A vector of Entity's are needed to be passed to the Renderer so that it knows which objects to render; More about Entity in the .cpp
	std::vector<AEON_ENGINE::GameObject*> m_containerList;

	//**These variables are used for a quick timestep and camera movement
	//**Do not alter these, they will be changed and properly implemented later on
	float lastX = 800 / 2; //Center of screen x
	float lastY = 600 / 2; //Center of screen y
	bool firstMouse = true;
	//Timing
	float deltaTime = 0.0f; //Time between current frame and last frame
	float lastFrame = 0.0f; //Time of last frame
};

#endif

//We will need to use a format like this in each class and update them every time we make a change to a document

//CHANGE LOG:
/*
	- Completed task A
	- Started task B
*/

//TODO:
/*
	- Task C
	- Task D
	- Task E
*/