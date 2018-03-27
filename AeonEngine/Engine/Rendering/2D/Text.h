#ifndef TEXT_H
#define TEXT_H

#include <glm/glm.hpp>

#include <string>

namespace AEON_ENGINE {

	class Text
	{
	public:
		Text();
		Text(std::string text_, float xpos_, float ypos_, float size_, glm::vec3 colour_ = glm::vec3(0.0f, 0.0f, 0.0f));
		~Text();

		//Setters
		void setText(std::string text_);
		void setPosition(float xpos_, float ypos_);
		void setCenterPosition(float xpos_, float ypos_);
		void setSize(float size_);
		void setColour(glm::vec3 colour_);
		void setHoverColour(glm::vec3 col_);
		void addTextLength(float w_, float h_);

		void toggleHoverState();

		std::string textContent;
		float xpos, ypos;
		float size;
		glm::vec3 colour, colour_hover, colour_saved;
		bool isHovered = false;
		glm::vec2 textLength = glm::vec2(0.0f, 0.0f);

	};

}


#endif