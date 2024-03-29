#include "Mesh.h"
#include "Model.h"

const unsigned int width = 1000;
const unsigned int height = 1000;
float texScale = 15.0f;

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, -0.2f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -0.2f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, texScale)},
	Vertex{glm::vec3(1.0f, -0.2f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(texScale, texScale)},
	Vertex{glm::vec3(1.0f, -0.2f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(texScale, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	//Cube Indices
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	glfwInit();

	//GLFW Versions + Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "RGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "No Window :(" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Current Window
	glfwMakeContextCurrent(window);

	//Loads OpenGL
	gladLoadGL();

	//Viewport Coordinates
	glViewport(0, 0, width, height);

	
	Texture textures[]
	{
		//Texture Object
		Texture("cobble_diff.png", "diffuse", 0),
		Texture("cobble_spec.png", "specular", 1),
		Texture("models/woof.png", "baseColor", 2)
	}; 

	//Creating General Shader
	Shader shaderProgram("default.vert", "default.frag");

	
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, ind, tex);
	

	//Creating Emissive Shaders
	Shader lightShader("light.vert", "light.frag");
	//Shader lightShader2("light.vert", "light.frag");
	//Shader lightShader3("light.vert", "light.frag");
	//Shader lightShader4("light.vert", "light.frag");


	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);

	//Setting up Light Cube
	glm::vec4 lightColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 0.0f, 2.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec4 lightColor2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 lightPos2 = glm::vec3(1.0f, 0.0f, -2.0f);
	glm::mat4 lightModel2 = glm::mat4(1.0f);
	lightModel2 = glm::translate(lightModel2, lightPos2);

	glm::vec4 lightColor3 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec3 lightPos3 = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 lightModel3 = glm::mat4(1.0f);
	lightModel3 = glm::translate(lightModel3, lightPos3);


	//Setting up Pyramid
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f); //find the xyz coords of the model
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	//Activating Various Shader Objects
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	//Rotation
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	shaderProgram.Activate();
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor2"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);

	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor3"), lightColor3.x, lightColor3.y, lightColor3.z, lightColor3.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos3"), lightPos3.x, lightPos3.y, lightPos3.z);


	//Enabling depth (no overlapping triangles)
	glEnable(GL_DEPTH_TEST);

	//Camera Object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model monke("models/monke.gltf");



	while (!glfwWindowShouldClose(window))
	{
		//Specify background color
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f); //Redifexx Blue
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Clean the back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		floor.Draw(shaderProgram, camera, glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(5));
		monke.Draw(shaderProgram, camera);

		//Swao the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents(); //update window
	}

	shaderProgram.Delete();
	lightShader.Delete();
	//lightShader2.Delete();
	//lightShader3.Delete();
	//lightShader4.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}