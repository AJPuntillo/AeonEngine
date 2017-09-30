#include <AeonEngine/Engine/Core/Window.h>
#include <AeonEngine/Engine/Graphics/Shader.h>

using namespace AEON_ENGINE;

#include "DemoGame.h"

int main(int argc, char* args[]) {
	//Grab an instance of the engine and then tell it that it has a game attached; 
	//IMPORTANT: Needs to be before the initialize()
	EngineCore::getInstance()->gameInterface = new DemoGame();

	//Create the first instance of our engine
	if (EngineCore::getInstance()->initialize()) {
		//Start the Game Loop
		EngineCore::getInstance()->run();
	}

	return 0;
}

//int main(int argc, char* args[]) {
//
//	Window *window = new Window();
//	window->initialize("Test Scene", 800, 600, 0);
//
//	//Shader Program
//	Shader demoShader("C:/Users/Andrew/Documents/Projects/C++ Projects/AeonEngine/AeonEngine/Engine/Graphics/Shaders/vertShaderTest.glsl", "C:/Users/Andrew/Documents/Projects/C++ Projects/AeonEngine/AeonEngine/Engine/Graphics/Shaders/fragShaderTest.glsl");
//
//	//Vertex structure
//	float vertices[] = {
//		-0.5f, -0.5f, 0.0f, // left  
//		 0.5f, -0.5f, 0.0f, // right 
//		 0.0f,  0.5f, 0.0f  // top   
//	};
//
//	GLuint VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	bool running = true;
//
//	while (running) {
//		//Rendering
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//Draw our first triangle
//		demoShader.use();
//
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//glBindVertexArray(0);
//
//		//Swap buffers
//		window->swapBuffers();
//	}
//
//	return 0;
//}