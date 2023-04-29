#version 330 core

// Pos + Coords + Texs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 curPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;


uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	curPos = vec3(model * vec4(aPos, 1.0f));
	Normal = aNormal;
	color = aColor;
	texCoord = aTex;

	// Outputs the pos/coords of all vertices
	gl_Position = camMatrix * vec4(curPos, 1.0);
}