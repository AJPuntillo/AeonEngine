#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVel;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform float time;
uniform float gravity;
uniform vec3 speed;
uniform vec4 colour;

out vec3 col;

void main()
{
	float t = time;
	col = vec3(sin(t), cos(t), sin(t));
	//col = vec3(0.5 - t, 0.5 - t, 1.0 - (t / 2));
	//vec4 vert = aPos + vec4(aVel * t, 0.0);
	vec3 vertPos = ((aVel * t) + (0.5*(vec3(0.0, gravity, 0.0) * (t * t))));
	
	for (int i = 0; i < 10; i++) {
		
	}
	
	gl_Position = projection * view * model * vec4(vertPos, 1.0);
}

