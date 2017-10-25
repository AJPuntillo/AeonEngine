# AeonEngine
Custom C++ engine

### DOCUMENTATION

#### [EngineCore Class]:

A singleton class that allows for initialization of an instance of the Engine Core. SDL and Glew are initialized along with the Window.
Has a static object of the Window class and the InputManager. Starts the gameloop and initializes the Game class (Game Interface).

*Public Methods*:
- static EngineCore* getInstance()
  - Retrieves the instance of the Engine that can be used to call its other methods.
- static void TerminateGame()
  - Cleans up all the objects contained within the class and sets them to nullptr.
- bool initialize()
  - Initializes the Engine.
- void run()
  - The gameloop. Calls the update, render, and draw methods.
- void update();
  - Updates the game.
- void render()
  - Renders the game.
- void draw()
  - Draws the game (UI elements, etc..).
- Window* getWindow() const
  - **[Getter]** Returns the Window object.
- SDL_Keycode getKeyPressed() const
  - **[Getter]** Returns the current key that has been pressed.
- InputManager getInputManager()
  - **[Getter]** Returns the InputManager object.

*Private Methods*:
- **void updateInput()**
  - Process and updates input through the InputManager.


### CHANGE LOG

**[10/01/17]**
- Started documentation
- Descriptions in the headers of each class
- Renderer class added (But needs proper implementation)

**[10/15/17]**
- Implemented the Renderer class
- Created Entity class that acts as the base object for more complex objects (Model, Light, etc)
- Camera now contains the View and Projection matrix and can be accessed by the Renderer
- All models contain their own Model matrix (also a translation, scale, and rotation matrix)

**[10/25/17]**
- Implemented the Skybox class
- PrimitiveModel and Model (Assimp) now working properly and can be rendered together through the Renderer
- Moved the GL renderer calls and swapbuffers calls outside of the renderer to prevent multiple double buffering calls and flickering
- Shader paths are fixed and no longer need absolute paths
- Models use their matrices correctly
- Added a new DemoScene that contains basic instructions on how to setup one


### TO DO

- Optimization/CPU Usuage
- Most optimal place for processing inputs
- ~~Model Class (Primitive and assimp)~~
- Lighting
- ~~Fix Shader class path~~
- Timing class
- Scene does not "delete" when switched to another scene
- Engine Core class should only initialize engine specific classes and any other user-specific preferences (eg. window size, which shaders to use) should be created somewhere else
- Process Input method for Game and Scene Interface
- Resizable window
- Physics
- Math
- Audio
- ~~Properly fix the Rendering classes and hook up the Renderer~~
- Finish Documentation
- Implement ResourceManager
- Components (?)
- ~~Localize matrices for each model~~
- ~~Fix transformations in model class~~
- ~~Textures~~
- ~~Asset Importer fix~~
x ~~Skybox method inside Renderer~~
x ~~LoadMesh()~~
x ~~Fix up the model.h/mesh.h~~
x ~~Look into the alpha problems with model loading~~
- Renderer usability (add/remove buffers, clear color, swap buffers, etc)
