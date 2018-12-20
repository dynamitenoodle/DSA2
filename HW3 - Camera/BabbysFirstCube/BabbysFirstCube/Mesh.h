#pragma once

//This is horrible and disgusting and you should feel bad.
//this is something that should be in a pre-compiled header
//like stdafx.h
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

/// <summary>
/// This represents on 'mesh' for our rendering pipeline
/// </summary>
class Mesh
{
public:
    /// <summary>
    /// Default constructor
    /// </summary>
    Mesh();
    
    /// <summary>
    /// Destruction!
    /// </summary>
    ~Mesh();

    /// <summary>
    /// Creates our VAO & VBO based on an array of vertices
    /// </summary>
    /// <param name="vertices">The array of vertices</param>
    /// <param name="count">The count of vertices</param>
    /// <param name="shaderProgram">The 'handle' to the shader program</param>
    void InitWithVertexArray(GLfloat vertices[], size_t count, GLuint shaderProgram);
    
    /// <summary>
    /// Bind our VAO and draw our shape!
    /// </summary>
    void Render();

	/// <summary>
	/// Sets which way we draw our object
	/// </summary>
	void SetDraw(bool set);

private:

	// which drawing mode?
	bool triangleDraw;

    //vector of vertices
    std::vector<GLfloat> vertices;
    
    //our VAO
    GLuint VAO;

    //our VBO
    GLuint VBO;
    
    //how many vertices we have
    GLsizei vertCount;

    /// <summary>
    /// Helper function to create the VAO & VBO
    /// </summary>
    /// <param name="shaderProgram">The 'handle' to the shader program to create the VAO for</param>
    void CreateBuffers(GLuint shaderProgram);
};

