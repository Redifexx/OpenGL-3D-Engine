#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.8f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
	glfwInit();



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //What major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //What minor verion
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //which profile

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f, //Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.32f, //Lower Right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	1.0f, 0.6f, 0.32f, //Upper Corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6,	0.0f,	0.9f, 0.45f, 0.17f, //Inner Left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,	0.0f,	0.9f, 0.45f, 0.17f, //Inner Right
		0.0f, -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f //Inner Down
	};


	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Yo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "No Window :(" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //This is the current window

	gladLoadGL(); //load open gl

	glViewport(0, 0, 800, 800); //where cords begin

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f); //set window color
		glClear(GL_COLOR_BUFFER_BIT); //set color buffer
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); //update window
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}