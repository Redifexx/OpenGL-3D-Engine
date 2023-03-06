#version 330 core

//Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;

in vec2 texCoord;

in vec3 Normal;
in vec3 curPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	//FragColor = vec4(color, 1.0f);
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - curPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 1.0f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	FragColor = (texture(tex0, texCoord) * lightColor * (diffuse + ambient)) + (texture(tex1, texCoord).g * specular);
	//FragColor = (texture(tex1, texCoord)) * specular;
	//FragColor = vec4(color, 1.0f);
}
