#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

#ifdef _DEBUG
#include <iostream>
#endif

///<summary>This represents one OpenGL shader instance, and provides API for initializing
///the shader and attaching it to a shader program</summary>
class Shader
{
private:
	GLuint shaderLoc;
public:
	///<summary>Default constructor</summary>
	Shader();

	///<summary>Destructor</summary>
	~Shader();

	///<summary>Initializes a shader by loading in a .glsl file and compiling it</summary>
	///<param name='filePath'>A string specifying the path of the file</param>
	///<param name='shaderType'>GLenum representing the type</param>
	///<returns>Wether or note the compilation succeeds</returns>
	bool InitFromFile(std::string filePath, GLenum shaderType);

	///<summary>Initializes a shader by compiling a string</summary>
	///<param name='filePath'>A string that makes up the .glsl file</param>
	///<param name='shaderType'>GLenum representing the type</param>
	///<returns>Wether or note the compilation succeeds</returns>
	bool InitFromString(std::string shaderCode, GLenum shaderType);

	///<summary>The location of the shader</summary>
	GLuint GetShaderLoc() const { return shaderLoc; }
};

