#include "stdafx.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameEntity.h"
#include "Material.h"
#include "Input.h"
#include <stdlib.h>
#include <time.h>  

//TODO - maybe make some #define macro for a print if debug?
//TODO - make an Engine class with a specific Init() and Run() function such that
//       our Main.cpp is kept clean and tidy

int main()
{
    {
		// get a random seed
		srand(time(NULL));

		//init GLFW
        {
            if (glfwInit() == GLFW_FALSE)
            {
#ifdef _DEBUG
                std::cout << "GLFW failed to initialize" << std::endl;
                _CrtDumpMemoryLeaks();
                std::cin.get();
#endif
                return 1;
            }
        }
#ifdef _DEBUG
        std::cout << "GLFW successfully initialized!" << std::endl;
#endif // _DEBUG

        //create & init window, set viewport
        int width = 800;
        int height = 600;
        GLFWwindow* window = glfwCreateWindow(width, height, "Babby's First Cube?", nullptr, nullptr);
        {
            if (window == nullptr)
            {
#ifdef _DEBUG
                std::cout << "GLFW failed to create window" << std::endl;
                _CrtDumpMemoryLeaks();
                std::cin.get();
#endif
                glfwTerminate();
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
#ifdef _DEBUG
        std::cout << "Window successfully initialized!" << std::endl;
#endif // _DEBUG

        //init GLEW
        {
            if (glewInit() != GLEW_OK)
            {
#ifdef _DEBUG
                std::cout << "GLEW failed to initialize" << std::endl;
                _CrtDumpMemoryLeaks();
                std::cin.get();
#endif
                glfwTerminate();
                return 1;
            }
        }
#ifdef _DEBUG
        std::cout << "GLEW successfully initialized!" << std::endl;
#endif // _DEBUG

        //init the shader program
        //TODO - this seems like a better job for a shader manager
        //       perhaps the Shader class can be refactored to fit a shader program
        //       rather than be a thing for vs and fs
        GLuint shaderProgram = glCreateProgram();
        {
            //create vS and attach to shader program
            Shader *vs = new Shader();
            vs->InitFromFile("assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
			
            glAttachShader(shaderProgram, vs->GetShaderLoc());

            //create FS and attach to shader program
            Shader *fs = new Shader();
            fs->InitFromFile("assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
            glAttachShader(shaderProgram, fs->GetShaderLoc());

            //link everything that's attached together
            glLinkProgram(shaderProgram);

            GLint isLinked;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
            if (!isLinked)
            {
                char infolog[1024];
                glGetProgramInfoLog(shaderProgram, 1024, NULL, infolog);
#ifdef _DEBUG
                std::cout << "Shader Program linking failed with error: " << infolog << std::endl;
                std::cin.get();
#endif

                // Delete the shader, and set the index to zero so that this object knows it doesn't have a shader.
                glDeleteProgram(shaderProgram);
                glfwTerminate();
                _CrtDumpMemoryLeaks();
                return 1;
            }

            //everything's in the program, we don't need this
            delete fs;
            delete vs;
        }

#ifdef _DEBUG
        std::cout << "Shaders compiled attached, and linked!" << std::endl;
#endif // _DEBUG

        //init the mesh (a cube)
        //TODO - replace this with model loading
        GLfloat cubeVertices[] = {
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

        //create our mesh & material
        //TODO - maybe have a MeshManager & a MaterialManager
		Mesh* cubeMesh = new Mesh();
		cubeMesh->InitWithVertexArray(cubeVertices, _countof(cubeVertices), shaderProgram);
		Material* material = new Material(shaderProgram);

        //TODO - maybe a GameEntityManager?
		GameEntity** myGameEntities = new GameEntity*[52];
		int entityCount = 0;

		/*Creating the GameEntities*/
		{
			// set the max distance the objects can spawn
			int maxDis = 501;

			// Set the around box
			myGameEntities[entityCount] = new GameEntity(
				cubeMesh,
				material,
				glm::vec3(0, 0, 0), 
				glm::vec3(0, 0, 0), 
				glm::vec3(3.5f, 3.5f, 3.5f) 
			);
			myGameEntities[entityCount]->NewColor(1.0f, 1.0f, 1.0f, .5f);
			entityCount++;

			for (int i = 0; i < 50; i++)
			{
				
				float ranX = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;
				float ranY = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;
				float ranZ = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;

				for (int j = 0; j < entityCount; j++)
				{
					while (myGameEntities[j]->GetDistance(ranX, ranY, ranZ) < 0.3f)
					{
						ranX = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;
						ranY = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;
						ranZ = ((rand() % maxDis) - (maxDis / 2)) / 100.0f;
					}
				}

				myGameEntities[entityCount] = new GameEntity(
					cubeMesh,
					material,
					glm::vec3(ranX, ranY, ranZ), // random position
					glm::vec3((rand() % 360) / 1.0f, (rand() % 360) / 1.0f, (rand() % 360) / 1.0f), // random rotation
					glm::vec3(0.25f, 0.25f, 0.25f) // scale to fit the screen
				);
				myGameEntities[entityCount]->NewColor(((rand() % 255) + 1) / 255.0f, ((rand() % 255) + 1) / 255.0f, ((rand() % 255) + 1) / 255.0f, 1.0f);
				entityCount++;
			}
		}

        //TODO - maybe a CameraManager?
        Camera* myCamera = new Camera(
            glm::vec3(0.0f, 0.0f, -8.f),    //position of camera
            glm::vec3(0.0f, 0.0f, 1.f),     //the 'forward' of the camera
            glm::vec3(0.0f, 1.f, 0.0f),     //what 'up' is for the camera
            60.0f,                          //the field of view in radians
            (float)width,                   //the width of the window in float
            (float)height,                  //the height of the window in float
            0.01f,                          //the near Z-plane
            100.f,                           //the far Z-plane
			window
        );

        Input::GetInstance()->Init(window);

        glEnable(GL_DEPTH_TEST);

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// enable culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

        glDepthFunc(GL_LESS);

        //main loop
		while (!glfwWindowShouldClose(window))
        {
            /* INPUT */
            {
                //checks events to see if there are pending input
                glfwPollEvents();

                //breaks out of the loop if user presses ESC
                if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                {
                    break;
                }

            }

            /* GAMEPLAY UPDATE */
			for (int i = 0; i < entityCount; i++)
			{
				if (i != 0)
					myGameEntities[i]->eulerAngles.y += 0.01f;

				myGameEntities[i]->Update();
			}
            myCamera->Update();

            /* PRE-RENDER */
            {
                //start off with clearing the 'color buffer'
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //clear the window to have p a s t e l o r a n g e
                glClearColor((255.0f/255.0f), (154.0f / 255.0f), (221.0f/255.0f), 1.0f);
            }

            /* RENDER */
			// Render the opaque
			for (int i = 1; i < entityCount; i++)
			{
				myGameEntities[i]->Render(myCamera);
			}

			// Render the transparent
			myGameEntities[0]->Render(myCamera);

            /* POST-RENDER */
            {
                //'clear' for next draw call
                glBindVertexArray(0);
                glUseProgram(0);
                //swaps the front buffer with the back buffer
                glfwSwapBuffers(window);
            }
        }

        //de-allocate our mesh!
		delete cubeMesh;
        delete material;
		for (int i = 0; i < entityCount; i++)
		{
			delete myGameEntities[i];
		}
        delete myCamera;
        Input::Release();
    }

    //clean up
    glfwTerminate();
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
    return 0;
}