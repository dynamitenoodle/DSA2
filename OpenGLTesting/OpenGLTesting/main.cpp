/*
Coehl Gleckner
9/6/2018
DSA 2
Following the Atlas examples for making a window and triangles (with Tanat's help)
*/

#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW\glfw3.h>

int main() {
	
	glfwInit();

	int screenWidth = 800;
	int screenHeight = 600;

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Howdy", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glfwMakeContextCurrent(window);

	//glewInit();
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, screenWidth, screenHeight);


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// 0.392f, 0.584f, 0.929f CORNFLOWER BLUEEEE
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}

	std::cin.get();
	return 0;

}