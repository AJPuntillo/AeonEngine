#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>   

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../Core/Window.h"
#include "../../Camera/Camera.h"
#include "../../DataStructures/ShaderManager.h"
#include "../../Graphics/Shader.h"
#include "Text.h"

namespace AEON_ENGINE {

	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	class TextRenderer
	{
	public:

		TextRenderer();
		~TextRenderer();

		const GLuint WIDTH = 800, HEIGHT = 600;


		void init(const char* filePath);
		
		void destroy();
		void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		void RenderText(Window* window, ShaderManager::HandleType shaderHandle_, std::vector<Text*> textList);
		void GetTextLength(std::vector<Text*> textList);
		
		void UpdateTextPosition(Window* window_, std::vector<Text*> textList);

	private:

		std::map<GLchar, Character> Characters;
		GLuint VAO, VBO;

		int oldWidth = 800;
		int oldHeight = 600;

	};

}
#endif