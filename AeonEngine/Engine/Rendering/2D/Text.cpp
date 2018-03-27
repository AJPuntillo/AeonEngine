#include "Text.h"

using namespace AEON_ENGINE;

Text::Text()
{
	textContent = "Text";
	xpos = 0.0f;
	ypos = 0.0f;
	size = 1.0f;
	colour = glm::vec3(0.0f, 0.0f, 0.0f);
	colour_hover = glm::vec3(1.0f, 1.0f, 1.0f);
	colour_saved = glm::vec3(0.0f, 0.0f, 0.0f);
}

Text::Text(std::string text_, float xpos_, float ypos_, float size_, glm::vec3 colour_)
{
	textContent = text_;
	xpos = xpos_;
	ypos = ypos_;
	size = size_;
	colour = colour_;
	colour_hover = colour_;
	colour_saved = colour_;
}

Text::~Text()
{

}

void Text::setText(std::string text_)
{
	textContent = text_;
}

void Text::setPosition(float xpos_, float ypos_)
{
	xpos = xpos_;
	ypos = ypos_;
}

void Text::setCenterPosition(float xpos_, float ypos_)
{
	setPosition(xpos_ - (textLength.x / 2), ypos_ /*- (textLength.y / 2)*/);
}

void Text::setSize(float size_)
{
	size = size_;
}

void Text::setColour(glm::vec3 colour_)
{
	colour = colour_;
}

void Text::setHoverColour(glm::vec3 col_)
{
	colour_hover = col_;
}

void Text::toggleHoverState()
{
	isHovered = !isHovered;

	if (isHovered) {
		colour_saved = colour;
		colour = colour_hover;
	}
	else
		colour = colour_saved;
}

void Text::addTextLength(float w_, float h_)
{
	textLength.x += w_;
	textLength.y += h_;
}