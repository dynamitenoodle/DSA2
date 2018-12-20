//OpenGL stuff
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>

//Memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "shader.h"

#ifdef _DEBUG
#include <iostream>
#endif

int main()
{
	//init GLFW
	{
		if (glfwInit() == GLFW_FALSE)
		{
#ifdef _DEBUG
			std::cout << "GLFW failed to initialize" << std::endl;
#endif
			std::cin.get();
			_CrtDumpMemoryLeaks();
			return 1;
			//no need to call glfwTerminate() here because init never happened
		}
	}

	glm::vec2(0.0f);

	//create & init window, set viewport
	GLFWwindow* window = glfwCreateWindow(800, 600, "Babby's First Cube", nullptr, nullptr);
	{
		if (window == nullptr)
		{
#ifdef _DEBUG
			std::cout << "GLFW failed to create window" << std::endl;
#endif
			glfwTerminate();
			_CrtDumpMemoryLeaks();
			return 1;
		}

		//tells OpenGL to use this window for this thread
		//(this would be more important for multi-threaded apps)
		glfwMakeContextCurrent(window);

		//gets the width & height of the window and specify it to the viewport
		int windowWidth, windowHeight;
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
	}

	//init GLEW
	{
		if (glewInit() != GLEW_OK) {
#ifdef _DEBUG
			std::cout << "GLEW failed to initialize" << std::endl;
#endif
			glfwTerminate();
			std::cin.get();
			_CrtDumpMemoryLeaks();
			return 1;
		}
	}

	//init the shader program
	GLuint shaderProgram = glCreateProgram();

	Shader *fragmentShader = new Shader();
	fragmentShader->InitFromFile("assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgram, fragmentShader->GetShaderLoc());

	Shader *vertexShader = new Shader();
	vertexShader->InitFromFile("assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	glAttachShader(shaderProgram, vertexShader->GetShaderLoc());

	glLinkProgram(shaderProgram);
	
	// init the mesh
	GLfloat vertices[] = {
		0.f, 1.f, 1.f,
		-1.f, -1.f, 1.f,
		1.f, -1.f, 1.f
	};

	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	//init the mesh
	delete vertexShader;
	delete fragmentShader;

	// vertex array object (how we describe data)
	GLuint VAO;
	glGenVertexArrays(1, &VAO); // create 1 'array', store i nVAO
	glBindVertexArray(VAO); // Tells OpenGL that this our descriptor 'array'

	// vertex buffer object (the data itself)
	GLuint VBO; 
	glGenBuffers(1, &VBO); // create 1 buffer, store in VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // tells OpenGL this is our memory 'array buffer'
	glBufferData(			// creates memory for this in the GPU 'buffer store'
		GL_ARRAY_BUFFER,    // the target
		sizeof(vertices),	// the size
		vertices,			// starting pointer
		GL_STATIC_DRAW		// 'hint' of what it's used for
	);

	GLuint attribIndex = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(
		attribIndex,			// location of attribute
		3,						// how many of that data
		GL_FLOAT,				// data type
		GL_FALSE,				// normalize?
		3 * sizeof(GLfloat),	// stride
		(GLvoid*)0				// offset	
	);
	glEnableVertexAttribArray(attribIndex);

	// clear out
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		{
			//checks events to see if there are pending input
			glfwPollEvents();

			//breaks out of the loop if user presses ESC
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				break;
			}
		}

		//Gameplay update


		//Preparing to Render
		{
			//start off with clearing the 'color buffer'
			glClear(GL_COLOR_BUFFER_BIT);

			//clear the window to have c o r n f l o w e r   b l u e
			glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		}

		//Render
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3); // triangle draw
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // indices starting at 0 -> 12 triangles -> 6 squares

		glBindVertexArray(0);
		glUseProgram(0); // clears out all shader programs

		//Clean-up after Render
		{
			//swaps the front buffer with the back buffer
			glfwSwapBuffers(window);
		}


	}

	//clean up
	glfwTerminate();
	_CrtDumpMemoryLeaks();
	return 0;
}