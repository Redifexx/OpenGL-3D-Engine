#version 330 core

// Pos + Coords
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;


layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

// Fragment Shader Color
out vec3 color;

out vec2 texCoord;

out vec3 Normal;
out vec3 curPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	curPos = vec3(model * vec4(aPos, 1.0f));


	// Outputs the pos/coords of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);

	//Assigns the colors from the vertex data to "color"
	color = aColor;
	texCoord = aTex;
	Normal = aNormal;
}