#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //What major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //What minor verion
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //which profile


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
	glClearColor(0.0f, 0.13f, 0.17f, 1.0f); //set window color
	glClear(GL_COLOR_BUFFER_BIT); //set color buffer
	glfwSwapBuffers(window); //swap buffers

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //update window
	}



	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}