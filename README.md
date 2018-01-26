# AeonEngine
Custom C++ engine

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
- Added a new TutorialScene that contains instructions on how to setup/use

**[10/27/17]**
- Added a basic Lighting class
- Fixed issues with texture binding for Primitive Models
- Added specular component to Primitive Models

**[10/29/17]**
- Added more lighting types in the Lighting class
- Changes in the Renderer to render different lighting types, but only Directional light is enabled until Advanced Lighting is further explored
- Added a post and pre render to the Renderer class to handle buffer calls
- Changes to the EngineCore initialize() to take in window parameters
- Added utility methods in the Window class for locking and unlocking the mouse to the window
- Added a processInput method in the EngineCore/SceneInterface/GameInterface and moved all the input code from the update

**[10/30/17]**
- Added Timer class that sets limits to the game loop (solved the CPU Usage problem) and tracks fps/delta time
- Added utility to the EngineCore's run method, allowing to print out fps/delta time and limiting fps
- Delta time is now passed from the EngineCore's game loop's timer to the scene's update
- Added resize methods to the Window class allowing the window to be resized
- Added a fullscreen method to the Window class allowing to toggle fullscreen
- Fixed issues with changing window focus; mouse is captured correctly now

**[11/08/17]**
- Added a Framebuffer class that allows the user to render the scene to a plane (Good for post-processing effects)
- PrimtiveModel now takes in a parameter to determine if it is rendering a Cube or a Plane

**[11/30/17]**
- Fixed the elusive texture binding bug (Was using Bind instead of Active)

**[01/25/18]**
- Added a GameObject class (Meant to contain Entity-type classes like Models)
- Added a Transform class that now handles all transformations and stores them into the model matrix
- Reworked the Renderer to use GameObjects
- Added a Resource Manager and Hashtable class that allows for quick storage and searching
- Added a Shader, Model, and Material Manager that inherits from the Resource Manager class
- Most shader calls are handled with Shader Handles for quick retrieval and optimization
- Added Pre/Post render methods to the Engine Core, Scene/Game Interface
- Updated the Tutorial Scene to reflect the recent changes

**[01/26/18]**
- Added BoundingVolumes class that detects AABB collisions
- Successfully merged the Model and PrimitiveModel class, allowing ease of use for other components (like BoundingVolumes)
- Removed PrimitiveModel and PrimitiveMesh classes
- GameObjects now all contain a BoundingVolume that can be set up when a model is attached to it

### TO DO

- Optimization
- Finish Documentation
- Advanced Lighting
- Scene does not "delete" when switched to another scene
- Physics (Adid)
- Math (Adid)
- ~~Audio~~ (Haifeng)
- 2D Graphics/HUD (Haifeng)
- Controller support (Fabio)
- Particle Engine
- ~~GameObject class~~
- ~~Pre/Post Render~~
- ~~Model Matrix check optimization~~
- ~~Implement ResourceManager~~
- ~~Face culling~~
- ~~Most optimal place for processing inputs~~
- ~~Model Class (Primitive and assimp)~~
- ~~Lighting~~
- ~~Fix Shader class path~~
- ~~Timing class~~
- ~~Engine Core class should only initialize engine specific classes and any other user-specific preferences (eg. window size, which shaders to use) should be created somewhere else~~
- ~~Process Input method for Game and Scene Interface~~
- ~~Resizable window/Fullscreen~~
- ~~Properly fix the Rendering classes and hook up the Renderer~~
- ~~Localize matrices for each model~~
- ~~Fix transformations in model class~~
- ~~Textures~~
- ~~Asset Importer fix~~
- ~~Skybox method inside Renderer~~
- ~~LoadMesh()~~
- ~~Fix up the model.h/mesh.h~~
- ~~Look into the alpha problems with model loading~~
- ~~Renderer usability (add/remove buffers, clear color, swap buffers, etc)~~
