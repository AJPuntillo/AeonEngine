#version 330 core

out vec4 FragColour;
in vec3 col;
void main()
{
	FragColour = vec4(col, 1.0f);
}