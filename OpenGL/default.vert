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

void main()
{
	// Outputs the pos/coords of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);

	//Assigns the colors from the vertex data to "color"
	color = aColor;
	texCoord = aTex;
}