//OpenGL stuff
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "shader.h"

#ifdef _DEBUG
#include <iostream>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"

int main()
{
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

        //create & init window, set viewport
        int width = 800;
        int height = 600;
        GLFWwindow* window = glfwCreateWindow(width, height, "Babby's First Cube?", nullptr, nullptr);
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
            if (glewInit() != GLEW_OK)
            {
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

        //create vS and attach to shader program
        Shader *vs = new Shader();
        vs->InitFromFile("assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
        glAttachShader(shaderProgram, vs->GetShaderLoc());

        //create FS and attach to shader program
        Shader *fs = new Shader();
        fs->InitFromFile("assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
        glAttachShader(shaderProgram, fs->GetShaderLoc());

        //link everything that's attached together
        glLinkProgram(shaderProgram);	//can also call get programiv to see if linking failed

        //everything's in the program, we don't need this
        delete fs;
        delete vs;

        //init the mesh
        GLfloat vertices[] = {
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f, 
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
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

		Mesh* myMesh = new Mesh();
		myMesh->InitWithVertexArray(vertices, _countof(vertices), shaderProgram);

		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::mat4 modelToWorld;
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

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

				if (glfwGetKey(window, GLFW_KEY_A))
				{
					position.x += 0.001f;
				}
				if (glfwGetKey(window, GLFW_KEY_D))
				{
					position.x -= 0.001f;
				}

				if (glfwGetKey(window, GLFW_KEY_W))
				{
					position.y += 0.001f;
				}
				if (glfwGetKey(window, GLFW_KEY_S))
				{
					position.y -= 0.001f;
				}

				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
				{
					position.z += 0.001f;
				}
				if (glfwGetKey(window, GLFW_KEY_SPACE))
				{
					position.z -= 0.001f;
				}
            }

            //Gameplay update
			modelToWorld = glm::translate(
				glm::identity<glm::mat4>(),
				//position.x,
				//glm::vec3(1.5f, -0.5f, .1f)
				position
			);


            //Preparing to Render
            {
                //start off with clearing the 'color buffer'
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //clear the window to have c o r n f l o w e r   b l u e
                glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
            }

            //enable shader
            glUseProgram(shaderProgram);

			glm::mat4 view = glm::lookAtLH(
				glm::vec3(0.0f, 0.0f, 5.f),
				glm::vec3(0.0f, 0.0f, -4.0f),
				glm::vec3(0.0f, 1.f, 0.0f)
			);

			glm::mat4 projection = glm::perspectiveFovLH<GLfloat>(
				60.0f * glm::pi<float>() / 180.0f,
				(float)width,
				(float)height,
				0.01f,
				100.f
			);

			GLuint viewMatLoc = glGetUniformLocation(
				shaderProgram,
				"viewMatrix"
			);
			glUniformMatrix4fv(
				viewMatLoc,
				1,
				GL_FALSE,
				&(view[0][0])
			);

			GLuint projectionMatLoc = glGetUniformLocation(
				shaderProgram,
				"projectionMatrix"
			);
			glUniformMatrix4fv(
				projectionMatLoc,
				1,
				GL_FALSE,
				&(projection[0][0])
			);

			GLuint modelToWorldLoc = glGetUniformLocation(
				shaderProgram,
				"modelToWorld"
			);
			glUniformMatrix4fv(
				modelToWorldLoc,
				1,
				GL_FALSE,
				&(modelToWorld[0][0])
			);

			myMesh->Render();

            //'clear' for next draw call
            glBindVertexArray(0);
            glUseProgram(0); 

            //Clean-up after Render
            {
                //swaps the front buffer with the back buffer
                glfwSwapBuffers(window);
            }

        }
			delete myMesh;
    }

    //clean up
    glfwTerminate();
    _CrtDumpMemoryLeaks();
    return 0;
}