#version 330 core

out vec4 FragColor;
in vec3 colourPos;

void main()
{
	FragColor = vec4(colourPos, 1.0);
}