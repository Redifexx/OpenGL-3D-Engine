
#version 330 core
//Outputs colors in RGBA
out vec4 FragColor;
in vec3 curPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec4 lightColor2;
uniform vec3 lightPos2;

uniform vec4 lightColor3;
uniform vec3 lightPos3;

uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVec = lightPos - curPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 5.0f / (a * dist * dist + b * dist + 1.0f);



	float ambient = 0.10f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 2.00f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity * lightColor + ambient) + texture(specular0, texCoord).r * specular * intensity * lightColor);
}

vec4 pointLight2()
{
	vec3 lightVec = lightPos2 - curPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 5.0f / (a * dist * dist + b * dist + 1.0f);



	float ambient = 0.10f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 2.00f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity * lightColor2 + ambient) + texture(specular0, texCoord).r * specular * intensity * lightColor2);
}

vec4 pointLight3()
{
	vec3 lightVec = lightPos3 - curPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 5.0f / (a * dist * dist + b * dist + 1.0f);



	float ambient = 0.00f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 2.00f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity * lightColor3 + ambient) + texture(specular0, texCoord).r * specular * intensity * lightColor3);
}



vec4 directionalLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	vec3 lightVec = lightPos - curPos;
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.80f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity * lightColor);
}

void main()
{
	FragColor = pointLight() + pointLight2() + pointLight3();
}