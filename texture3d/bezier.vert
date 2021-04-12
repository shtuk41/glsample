#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
uniform mat4 MVP;

out vec4 colorOut;

void main()
{
	//position of the vertex in clip space
	gl_Position = MVP * vec4(vPosition, 1.0);
	colorOut = vec4(vColor,1.0);
}