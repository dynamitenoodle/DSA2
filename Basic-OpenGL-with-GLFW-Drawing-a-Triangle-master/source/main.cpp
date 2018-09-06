/*
Title: Drawing a Triangle
File Name: Main.cpp
Copyright � 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "GL/glew.h"
#include "GLFW/glfw3.h"


// Vbo stands for Vertex Buffer Object
// This is just a fancy name for "A collection of vertices that we send to the graphics card"
GLuint vbo;


// GLuint is an open[GL] [U]nsigned [Int].
// It is literally just a typedefed unsigned int.
// OpenGL uses these as references to the internal graphics resources you create.


// This function resizes the viewport (rectangle gl renders to inside the window) to match the size of the window.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char **argv)
{
	// Initializes the GLFW library
	glfwInit();

	// Creates a window given (width, height, title, monitorPtr, windowPtr).
	// The last two control monitors for fullescreen mode, and using multiple windows. Leaving them as nullptr is fine.
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle!", nullptr, nullptr);

	// Changes our current OpenGL context to match that of the window.
	// This becomes more complex in relation to threading, but essentially tells openGL to use this window.
	glfwMakeContextCurrent(window);

	// Here we set up a callback with our viewport resizing function.
	// If the window changes size, we will resize the viewport.
	/// Try commenting this out and see what happens when you resize.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initializes the glew library, which adds some functionality we will need.
	glewInit();








	// Create data needed to render a triangle.


	// Create an array of vertices (this is our triangle coordinate data)
	// OpenGL draws geometry using screen coordinates.
	// (-1, -1) is the bottom left corner of the screen, and (1, 1) is the top right corner.
	/// Try changing them to see what happens.
	float vertices[] = {
		-.5, -.5,
		.5, .5,
		.5, -.5 };

	// This function makes space for our vertex buffer object
	// The first parameter is the number of buffer objects we want to make space for.
	// The second parameter is a pointer to an empty GLuint, which the function will fill. (in this case our vbo)
	// Once the buffers have been created, the function puts a reference to them in our vbo variable.
	glGenBuffers(1, &vbo);


	// This assigns assigns our vbo to a binding location called GL_ARRAY_BUFFER.
	// Any other functions that operate on GL_ARRAY_BUFFER will be using the currently bound vbo.
	// Binding with another vbo replaces previous one. Binding with 0 unbinds without binding anything new.
	// Other binding locations can be used for different kinds of buffers.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	// Here we copy or "buffer" our vertices into the vbo thats bound to GL_ARRAY_BUFFER.
	// We have to pass the size, and location of the vertices in memory.
	// The last parameter tells openGL how we plan on using the data.
	// In this example we are using STATIC, because our data won't change, and DRAW, because we will send it to the GPU to be drawn.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &vertices[0], GL_STATIC_DRAW);


	// Here we unbind the GL_ARRAY_BUFFER
	// We're only drawing one thing, so this isn't required, but it's good practice, and can help prevent bugs.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	



	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen
		// Tell openGL which "buffer" we want to clear
		// This takes a bitfield, meaning multiple buffers can be cleared at the same time with |
		glClear(GL_COLOR_BUFFER_BIT);

		// Clear the screen to black nothingness
		/// This can be changed to any rbga color. Values are between 0 and 1.
		glClearColor(0.0, 0.0, 0.0, 0.0);
		









		// Prepare to draw geometry

		// A Vertex Attribute Array is a collection of information about a vbo on the GPU.
		// The index indicates where the information will be located (for this specific draw call).
		// OpenGL defines a maximum number of these with a constant named GL_MAX_VERTEX_ATTRIBS.
		GLuint vertexAttribArrayIndex = 0;

		// Bind the vbo we want to use
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Here we set up our vertexAttribArray with the following:
		// 1) the index of the vertexAttribArray we want to use.
		// 2) the number of values each vertex has: 2 floats (max 4)
		// 3) the type that each piece of data is: GL_FLOAT (OpenGL uses a constant)
		// 4) whether or not to normalize the vectors: false (useful if vectors are directions)
		// 5) the stride (length in bytes) between the data. Ours is the same as the size, but it can be different. (storing additional data with each vertex)
		// 6) the offset into the buffer where we want to start. (the beginning) (For some reason this is a pointer)
		// This function uses whatever buffer is currently bound to the GL_ARRAY_BUFFER
		glVertexAttribPointer(vertexAttribArrayIndex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*) (sizeof(float) * 0));

		// At this point we are done using our vbo, so we can unbind it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);








		// Next we have to tell OpenGL that we intend to use the Vertex Attribute Array at the index we just set up.
		// If we don't, the data will never be sent to the gpu.
		glEnableVertexAttribArray(vertexAttribArrayIndex);

		// FINALLY, we get to our draw call.
		// 0 is the offset of our first vertex.
		// 3 is the number of vertices we want to use.
		// We also select the draw mode here:
		// GL_TRIANGLES takes every 3 vertices and draws them as a triangle.
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// When we are finished using our Vertex Attribute Array, we disable it.
		// This isn't required, because we are only rendering one object, but it's good practice.
		glDisableVertexAttribArray(vertexAttribArrayIndex);







		// So we've drawn our geometry, but it's actually being written to an offscreen image called the back buffer.
		// This prevents the image on screen from displaying to your monitor halfway through rendering.
		// Once rendering is complete, we can swap the image on screen with the one in the background.
		glfwSwapBuffers(window);

		// Checks to see if any events are pending and then processes them.
		// With this, we can get input, or update the viewport when the window resizes.
		glfwPollEvents();

	}








	// the opposite of glGenBuffers from above.
	// It's important to delete buffers when finished using them, or you will have memory leaks!
	glDeleteBuffers(1, &vbo);


	// Frees up GLFW memory
	glfwTerminate();

	// End of Program.
	return 0;
}
