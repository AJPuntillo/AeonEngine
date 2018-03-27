#include "TextRenderer.h"

using namespace AEON_ENGINE;

TextRenderer::TextRenderer()
{

}


TextRenderer::~TextRenderer()
{

}

void TextRenderer::init(const char* filePath)
{
	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, filePath, 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}



void TextRenderer::destroy() 
{

}

void TextRenderer::RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{


	// Set OpenGL options

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //blends text to background

	// Activate corresponding render state	
	shader.use();
	glUniform3f(glGetUniformLocation(shader.getShaderProgram(), "textColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);          //glEnable() always end with a disable~   
}

void TextRenderer::RenderText(Window* window_, ShaderManager::HandleType shaderHandle_, std::vector<Text*> textList)
{
	int screenWidth = window_->getScreenWidth();
	int screenHeight = window_->getScreenHeight();

	Shader* shader = ShaderManager::getInstance()->getShader(shaderHandle_);

	// Set OpenGL options

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //blends text to background

	shader->use();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(screenWidth), 0.0f, static_cast<GLfloat>(screenHeight));
	shader->setMat4("projection", projection);

	for (Text* ptTemp : textList) {
		Text text = *ptTemp;
		//glUniform3f(glGetUniformLocation(shader->getShaderProgram(), "textColor"), text.colour.x, text.colour.y, text.colour.z);
		shader->setVec3("textColor", text.colour);

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// Iterate through all characters
		std::string::const_iterator c;
		int i = 0;
		for (c = text.textContent.begin(); c != text.textContent.end(); c++)
		{
			i++;
			Character ch = Characters[*c];

			GLfloat xpos = text.xpos + ch.Bearing.x * text.size;
			GLfloat ypos = text.ypos - (ch.Size.y - ch.Bearing.y) * text.size;

			GLfloat w = ch.Size.x * text.size;
			GLfloat h = ch.Size.y * text.size;
			text.addTextLength(w, h);
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			text.xpos += (ch.Advance >> 6) * text.size; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glDisable(GL_BLEND);          //glEnable() always end with a disable~   
}

void TextRenderer::UpdateTextPosition(Window* window_, std::vector<Text*> textList)
{
	if (oldWidth != window_->getScreenWidth() || oldHeight != window_->getScreenHeight()) {
		for (Text* text : textList) {
			float xratio = text->xpos / oldWidth;
			float yratio = text->ypos / oldHeight;
			float newxpos = window_->getScreenWidth() * xratio;
			float newypos = window_->getScreenHeight() * yratio;
			text->setPosition(newxpos, newypos);
		}

		oldWidth = window_->getScreenWidth();
		oldHeight = window_->getScreenHeight();
	}
}

void TextRenderer::GetTextLength(std::vector<Text*> textList)
{
	for (Text* text : textList) {
		// Iterate through all characters
		std::string::const_iterator c;
		int i = 0;
		for (c = text->textContent.begin(); c != text->textContent.end(); c++)
		{
			i++;
			Character ch = Characters[*c];

			GLfloat w = ch.Size.x * text->size;
			GLfloat h = ch.Size.y * text->size;
			text->addTextLength(w, h);
		}
	}
}