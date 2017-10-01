# AeonEngine
Custom C++ engine

### DOCUMENTATION

####[EngineCore Class]:

A singleton class that allows for initialization of an instance of the Engine Core. SDL and Glew are initialized along with the Window.
Has a static object of the Window class and the InputManager. Starts the gameloop and initializes the Game class (Game Interface).

*Public Methods*:
- **static EngineCore* getInstance();**
  - Retrieves the instance of the Engine that can be used to call its other methods.
- **static void TerminateGame();**
  - Cleans up all the objects contained within the class and sets them to nullptr.
- **bool initialize();**
  - Initializes the Engine.
- **void run();**
  - The gameloop. Calls the update, render, and draw methods.
- **void update();**
  - Updates the game.
- **void render();**
  - Renders the game.
- **void draw();**
  - Draws the game (UI elements, etc..).
- **Window* getWindow() const**
  - **[Getter]** Returns the Window object.
- **SDL_Keycode getKeyPressed() const**
  - **[Getter]** Returns the current key that has been pressed.
- **InputManager getInputManager()**
  - **[Getter]** Returns the InputManager object.

*Private Methods*:
- void updateInput();
  - Process and updates input through the InputManager.


### CHANGE LOG

**[10/01/17]**
- Started documentation
- Descriptions in the headers of each class
- Renderer class added (But needs proper implementation)


### TO DO

- Optimization
- Most optimal place for processing inputs
- Model Class (Primitive and assimp)
- Lighting
- Fix Shader class path
- Timing class
- Scene does not "delete" when switched to another scene
- Engine Core class should only initialize engine specific classes and any other user-specific preferences (eg. window size, which shaders to use) should be created somewhere else
- Process Input method for Game and Scene Interface
- Resizable window
- Physics
- Math
- Audio
- Properly fix the Rendering classes and hook up the Renderer
- Finish Documentation
