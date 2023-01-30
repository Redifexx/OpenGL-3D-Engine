#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;


GLfloat vertices[] =
{   //		Coords			//		Colors			// TexCoords
	-0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Lower Left
	-0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f, // Upper Left
	 0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Upper Right
	 0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f, 	5.0f, 0.0f,
	 0.0f,	0.8f,	0.0f,		0.92f, 0.86f, 0.76f, 	2.5f, 5.0f
};



GLuint indices[] =
{
	0, 1, 2, 
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
	glfwInit();



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //What major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //What minor verion
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //which profile

	GLFWwindow* window = glfwCreateWindow(width, height, "RedGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "No Window :(" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //This is the current window

	gladLoadGL(); //load open gl

	glViewport(0, 0, width, height); //where cords begin

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	//Texture
	
	Texture monke("LLL32.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	monke.texUnit(shaderProgram, "tex0", 0);


	glEnable(GL_DEPTH_TEST); //Enabling depth

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		//Specify background color
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);

		//Clean the back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Tells OpenGL which Shader Program to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//Binds Texture
		monke.Bind();

		//Binds the VAO so OpenGL knows to use it
		VAO1.Bind();

		//Draws primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//Swao the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents(); //update window
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	monke.Delete();

	shaderProgram.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}