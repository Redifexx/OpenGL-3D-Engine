#version 330 core

// Pos + Coords
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;


layout (location = 2) in vec2 aTex;

// Fragment Shader Color
out vec3 color;

out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

//Controls mat
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// Outputs the pos/coords of all vertices
	gl_Position = proj * view * model * vec4(aPos, 1.0);

	//Assigns the colors from the vertex data to "color"
	color = aColor;
	texCoord = aTex;
}