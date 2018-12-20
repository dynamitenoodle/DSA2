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
        GLFWwindow* window = glfwCreateWindow(width, height, "Shapes Moving", nullptr, nullptr);
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
		// the first circle
		GLfloat verticesCircle[1080];
		GLfloat angle = 0;
		GLfloat radians = 0;
		GLfloat z = 1.0f;

		for (int i = 0; i < 1080; i++)
		{
			if (i % 9 == 0)
			{
				verticesCircle[i] = cos(radians);
			}

			if (i % 9 == 1)
			{
				verticesCircle[i] = sin(radians);
			}

			if (i % 9 == 2)
			{
				verticesCircle[i] = z;
			}

			if (i % 9 == 3)
			{
				verticesCircle[i] = 0.0f;
			}

			if (i % 9 == 4)
			{
				verticesCircle[i] = 0.0f;
			}

			if (i % 9 == 5)
			{
				verticesCircle[i] = z;

				angle += 1;
				radians += (angle) * (glm::pi<float>() / 180);
			}

			if (i % 9 == 6)
			{
				verticesCircle[i] = cos(radians);
			}

			if (i % 9 == 7)
			{
				verticesCircle[i] = sin(radians);
			}

			if (i % 9 == 8)
			{
				verticesCircle[i] = z;
			}
		}

		// the second circle
		GLfloat verticesCircle2[1080];
		angle = 0;
		radians = 0;
		z = -1.0f;

		for (int i = 0; i < 1080; i++)
		{
			if (i % 9 == 0)
			{
				verticesCircle2[i] = cos(radians);
			}

			if (i % 9 == 1)
			{
				verticesCircle2[i] = sin(radians);
			}

			if (i % 9 == 2)
			{
				verticesCircle2[i] = z;
			}

			if (i % 9 == 3)
			{
				verticesCircle2[i] = 0.0f;
			}

			if (i % 9 == 4)
			{
				verticesCircle2[i] = 0.0f;
			}

			if (i % 9 == 5)
			{
				verticesCircle2[i] = z;

				angle += 1;
				radians += (angle) * (glm::pi<float>() / 180);
			}

			if (i % 9 == 6)
			{
				verticesCircle2[i] = cos(radians);
			}

			if (i % 9 == 7)
			{
				verticesCircle2[i] = sin(radians);
			}

			if (i % 9 == 8)
			{
				verticesCircle2[i] = z;
			}
		}

		// the total amount of vertices
		GLfloat verticesTotal[4320];

		// create the center of the cylinder
		for (int i = 0; i < 1080; i++) 
		{
			// Point 1
			if (i % 9 == 0)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}
			if (i % 9 == 1)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}
			if (i % 9 == 2)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}

			// Point 2
			if (i % 9 == 3)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}
			if (i % 9 == 4)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}
			if (i % 9 == 5)
			{
				verticesTotal[i] = verticesCircle[i];
				verticesTotal[i + 1080] = verticesCircle2[i];
			}

			// Point 3, Reversed
			if (i % 9 == 6)
			{
				verticesTotal[i] = verticesCircle2[i];
				verticesTotal[i + 1080] = verticesCircle[i];
			}
			if (i % 9 == 7)
			{
				verticesTotal[i] = verticesCircle2[i];
				verticesTotal[i + 1080] = verticesCircle[i];
			}
			if (i % 9 == 8)
			{
				verticesTotal[i] = verticesCircle2[i];
				verticesTotal[i + 1080] = verticesCircle[i];
			}
		}

		// add the circles
		for (int i = 0; i < 1080; i++)
		{
			verticesTotal[i + 2160] = verticesCircle[i];
			verticesTotal[i + 3240] = verticesCircle2[i];
		}

		Mesh* cynlinderMesh = new Mesh();
		cynlinderMesh->InitWithVertexArray(verticesTotal, _countof(verticesTotal), shaderProgram);

		glm::float32 rotAngle = 0;
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

				// Z Change
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				{
					rotAngle += .05f;
				}

				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				{
					rotAngle -= .05f;
				}
            }

            //Gameplay update
			modelToWorld = glm::rotate(
				glm::identity<glm::mat4>(),
				rotAngle,
				glm::vec3(0, 1, 0)
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

			cynlinderMesh->Render();

            //'clear' for next draw call
            glBindVertexArray(0);
            glUseProgram(0); 

            //Clean-up after Render
            {
                //swaps the front buffer with the back buffer
                glfwSwapBuffers(window);
            }

        }
		delete cynlinderMesh;
    }

    //clean up
    glfwTerminate();
    _CrtDumpMemoryLeaks();
    return 0;
}

// old code

/*
GLfloat verticesCircle[1080];
GLfloat radius = 1;
int triangleAmount = 1080;
//int i = 0;
//int count = 0;

// loop for number of subdivisions
for (int i = 0; i < triangleAmount; i++)
{
/*
// create points
glm::vec3 pointA = glm::vec3(radius * cos((2.0f * PI) * i / (float)subdivisions), radius * sin((2.0f * PI) * i / (float)subdivisions), 0);
glm::vec3 pointB = glm::vec3(radius * cos((2.0f * PI) * (i + 1) / (float)subdivisions), radius*sin((2.0f * PI) * (i + 1) / (float)subdivisions), 0);
glm::vec3 pointC = glm::vec3(0, 0, 0);

cout << count << endl;
// add tri to the mesh
if (i == 0)
{
verticesCircle[count]  << endl = pointA.x;
count++;
verticesCircle[count]  << endl = pointA.y;
count++;
verticesCircle[count]  << endl = pointA.z;
count++;

verticesCircle[count]  << endl = pointB.x;
count++;
verticesCircle[count]  << endl = pointB.y;
count++;
verticesCircle[count]  << endl = pointB.z;
count++;

verticesCircle[count]  << endl = pointC.x;
count++;
verticesCircle[count]  << endl = pointC.y;
count++;
verticesCircle[count]  << endl = pointC.z;
count++;
}
else
{
verticesCircle[count]  << endl = pointA.x;
count++;
verticesCircle[count]  << endl = pointA.y;
count++;
verticesCircle[count]  << endl = pointA.z;
count++;

verticesCircle[count]  << endl = pointB.x;
count++;
verticesCircle[count]  << endl = pointB.y;
count++;
verticesCircle[count]  << endl = pointB.z;
count++;

verticesCircle[count]  << endl = pointC.x;
count++;
verticesCircle[count]  << endl = pointC.y;
count++;
verticesCircle[count]  << endl = pointC.z;
count++;
}
*/
/*
if (i == 0)
{
verticesCircle[0] = (GLfloat)(radius * cos(i * (glm::pi<float>() * 2.0f) / triangleAmount));
cout << verticesCircle[count]  << endl;
count++;
verticesCircle[count] = (GLfloat)(radius * sin(i * (glm::pi<float>() * 2.0f) / triangleAmount));
cout << verticesCircle[count]  << endl;
count++;
verticesCircle[count] = 0.0f;
cout << verticesCircle[count]  << endl;
count++;
}

else
{
verticesCircle[count] = (GLfloat)(radius * cos(i * (glm::pi<float>() * 2.0f) / triangleAmount));
cout << verticesCircle[count]  << endl;
count++;
verticesCircle[count] = (GLfloat)(radius * sin(i * (glm::pi<float>() * 2.0f) / triangleAmount));
cout << verticesCircle[count]  << endl;
count++;
verticesCircle[count] = 0.0f;
cout << verticesCircle[count]  << endl;
count++;
}
*/
/*
if (i % 3 == 0)
{
verticesCircle[i] = (GLfloat)(radius * cos(i * (glm::pi<float>() * 2.0f) / triangleAmount));
}

if (i % 3 == 1)
{
verticesCircle[i] = (GLfloat)(radius * sin(i * (glm::pi<float>() * 2.0f) / triangleAmount));

}

if (i % 3 == 2)
{
verticesCircle[i] = 0.0f;
}
}
*/


//#include "stdafx.h"
//#include "Shader.h"
//#include "Mesh.h"
//#include "Camera.h"
//#include "GameEntity.h"
//#include "Material.h"
//#include "Input.h"

//TODO - maybe make some #define macro for a print if debug?
//TODO - make an Engine class with a specific Init() and Run() function such that
//       our Main.cpp is kept clean and tidy

//int main()
//{
//	{
//		//init GLFW
//		{
//			if (glfwInit() == GLFW_FALSE)
//			{
//#ifdef _DEBUG
//				std::cout << "GLFW failed to initialize" << std::endl;
//				_CrtDumpMemoryLeaks();
//				std::cin.get();
//#endif
//				return 1;
//			}
//		}
//#ifdef _DEBUG
//		std::cout << "GLFW successfully initialized!" << std::endl;
//#endif // _DEBUG
//
//		//create & init window, set viewport
//		int width = 800;
//		int height = 600;
//		GLFWwindow* window = glfwCreateWindow(width, height, "Babby's First Cube?", nullptr, nullptr);
//		{
//			if (window == nullptr)
//			{
//#ifdef _DEBUG
//				std::cout << "GLFW failed to create window" << std::endl;
//				_CrtDumpMemoryLeaks();
//				std::cin.get();
//#endif
//				glfwTerminate();
//				return 1;
//			}
//
//			//tells OpenGL to use this window for this thread
//			//(this would be more important for multi-threaded apps)
//			glfwMakeContextCurrent(window);
//
//			//gets the width & height of the window and specify it to the viewport
//			int windowWidth, windowHeight;
//			glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
//			glViewport(0, 0, windowWidth, windowHeight);
//		}
//#ifdef _DEBUG
//		std::cout << "Window successfully initialized!" << std::endl;
//#endif // _DEBUG
//
//		//init GLEW
//		{
//			if (glewInit() != GLEW_OK)
//			{
//#ifdef _DEBUG
//				std::cout << "GLEW failed to initialize" << std::endl;
//				_CrtDumpMemoryLeaks();
//				std::cin.get();
//#endif
//				glfwTerminate();
//				return 1;
//			}
//		}
//#ifdef _DEBUG
//		std::cout << "GLEW successfully initialized!" << std::endl;
//#endif // _DEBUG
//
//		//init the shader program
//		//TODO - this seems like a better job for a shader manager
//		//       perhaps the Shader class can be refactored to fit a shader program
//		//       rather than be a thing for vs and fs
//		GLuint shaderProgram = glCreateProgram();
//		{
//
//			//create vS and attach to shader program
//			Shader *vs = new Shader();
//			vs->InitFromFile("assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
//			glAttachShader(shaderProgram, vs->GetShaderLoc());
//
//			//create FS and attach to shader program
//			Shader *fs = new Shader();
//			fs->InitFromFile("assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
//			glAttachShader(shaderProgram, fs->GetShaderLoc());
//
//			//link everything that's attached together
//			glLinkProgram(shaderProgram);
//
//			GLint isLinked;
//			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
//			if (!isLinked)
//			{
//				char infolog[1024];
//				glGetProgramInfoLog(shaderProgram, 1024, NULL, infolog);
//#ifdef _DEBUG
//				std::cout << "Shader Program linking failed with error: " << infolog << std::endl;
//				std::cin.get();
//#endif
//
//				// Delete the shader, and set the index to zero so that this object knows it doesn't have a shader.
//				glDeleteProgram(shaderProgram);
//				glfwTerminate();
//				_CrtDumpMemoryLeaks();
//				return 1;
//			}
//
//			//everything's in the program, we don't need this
//			delete fs;
//			delete vs;
//		}
//
//#ifdef _DEBUG
//		std::cout << "Shaders compiled attached, and linked!" << std::endl;
//#endif // _DEBUG
//
//		//init the mesh (a cube)
//		//TODO - replace this with model loading
//		GLfloat vertices[] = {
//			-1.0f,-1.0f,-1.0f, // triangle 1 : begin
//			-1.0f,-1.0f, 1.0f,
//			-1.0f, 1.0f, 1.0f, // triangle 1 : end
//			1.0f, 1.0f,-1.0f, // triangle 2 : begin
//			-1.0f,-1.0f,-1.0f,
//			-1.0f, 1.0f,-1.0f, // triangle 2 : end
//			1.0f,-1.0f, 1.0f,
//			-1.0f,-1.0f,-1.0f,
//			1.0f,-1.0f,-1.0f,
//			1.0f, 1.0f,-1.0f,
//			1.0f,-1.0f,-1.0f,
//			-1.0f,-1.0f,-1.0f,
//			-1.0f,-1.0f,-1.0f,
//			-1.0f, 1.0f, 1.0f,
//			-1.0f, 1.0f,-1.0f,
//			1.0f,-1.0f, 1.0f,
//			-1.0f,-1.0f, 1.0f,
//			-1.0f,-1.0f,-1.0f,
//			-1.0f, 1.0f, 1.0f,
//			-1.0f,-1.0f, 1.0f,
//			1.0f,-1.0f, 1.0f,
//			1.0f, 1.0f, 1.0f,
//			1.0f,-1.0f,-1.0f,
//			1.0f, 1.0f,-1.0f,
//			1.0f,-1.0f,-1.0f,
//			1.0f, 1.0f, 1.0f,
//			1.0f,-1.0f, 1.0f,
//			1.0f, 1.0f, 1.0f,
//			1.0f, 1.0f,-1.0f,
//			-1.0f, 1.0f,-1.0f,
//			1.0f, 1.0f, 1.0f,
//			-1.0f, 1.0f,-1.0f,
//			-1.0f, 1.0f, 1.0f,
//			1.0f, 1.0f, 1.0f,
//			-1.0f, 1.0f, 1.0f,
//			1.0f,-1.0f, 1.0f
//		};
//
//		GLfloat verticesCircle[1080];
//		GLfloat angle = 0;
//		GLfloat radians = 0;
//		
//		for (int i = 0; i < 1080; i++)
//		{
//			if (i % 9 == 0)
//			{
//				verticesCircle[i] = cos(radians);
//			}
//		
//			if (i % 9 == 1)
//			{
//				verticesCircle[i] = sin(radians);
//			}
//		
//			if (i % 9 == 2)
//			{
//				verticesCircle[i] = 0.0f;
//			}
//		
//			if (i % 9 == 3)
//			{
//				verticesCircle[i] = 0.0f;
//			}
//		
//			if (i % 9 == 4)
//			{
//				verticesCircle[i] = 0.0f;
//			}
//		
//			if (i % 9 == 5)
//			{
//				verticesCircle[i] = 0.0f;
//		
//				angle += 1;
//				radians += (angle) * (glm::pi<float>() / 180);
//			}
//		
//			if (i % 9 == 6)
//			{
//				verticesCircle[i] = cos(radians);
//			}
//		
//			if (i % 9 == 7)
//			{
//				verticesCircle[i] = sin(radians);
//			}
//		
//			if (i % 9 == 8)
//			{
//				verticesCircle[i] = 0.0f;
//			}
//		}
//
//		//create our mesh & material
//		//TODO - maybe have a MeshManager & a MaterialManager
//		Mesh* myMesh = new Mesh();
//		myMesh->InitWithVertexArray(vertices, _countof(vertices), shaderProgram);
//		Material* myMaterial = new Material(shaderProgram);
//
//		//TODO - maybe a GameEntityManager?
//		GameEntity* myGameEntity = new GameEntity(
//			myMesh,
//			myMaterial,
//			glm::vec3(0.f, 0.f, 0.f),
//			glm::vec3(0.f, 0.f, 0.f),
//			glm::vec3(1.f, 1.f, 1.f)
//		);
//
//		//TODO - maybe a CameraManager?
//		Camera* myCamera = new Camera(
//			glm::vec3(0.0f, 0.0f, -5.f),    //position of camera
//			glm::vec3(0.0f, 0.0f, 1.f),     //the 'forward' of the camera
//			glm::vec3(0.0f, 1.f, 0.0f),     //what 'up' is for the camera
//			60.0f,                          //the field of view in radians
//			(float)width,                   //the width of the window in float
//			(float)height,                  //the height of the window in float
//			0.01f,                          //the near Z-plane
//			100.f                           //the far Z-plane
//		);
//
//		Input::GetInstance()->Init(window);
//
//		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_LESS);
//
//		//main loop
//		while (!glfwWindowShouldClose(window))
//		{
//			/* INPUT */
//			{
//				//checks events to see if there are pending input
//				glfwPollEvents();
//
//				//breaks out of the loop if user presses ESC
//				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//				{
//					break;
//				}
//			}
//
//			/* GAMEPLAY UPDATE */
//			myGameEntity->Update();
//			myCamera->Update();
//
//			/* PRE-RENDER */
//			{
//				//start off with clearing the 'color buffer'
//				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//				//clear the window to have c o r n f l o w e r   b l u e
//				glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
//			}
//
//			/* RENDER */
//			myGameEntity->Render(myCamera);
//
//			/* POST-RENDER */
//			{
//				//'clear' for next draw call
//				glBindVertexArray(0);
//				glUseProgram(0);
//				//swaps the front buffer with the back buffer
//				glfwSwapBuffers(window);
//			}
//		}
//
//		//de-allocate our mesh!
//		delete myMesh;
//		delete myMaterial;
//		delete myGameEntity;
//		delete myCamera;
//		Input::Release();
//	}
//
//	//clean up
//	glfwTerminate();
//#ifdef _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//	return 0;
//}