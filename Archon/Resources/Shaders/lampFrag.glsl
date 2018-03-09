#version 330 core

out vec4 FragColour;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;

vec3 primitiveColour;

void main()
{    
	primitiveColour = vec3(0.9f, 0.9f, 0.9f);
    FragColour = vec4(primitiveColour, 1.0);
}