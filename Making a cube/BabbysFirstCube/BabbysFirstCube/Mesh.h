#pragma once

#define GLEW_STATIC
using namespace std;
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void InitWithVertexArray(GLfloat vetices[], size_t count, GLuint shaderProgram);
	void Render();

private:
	std::vector<GLfloat> vertices;
	GLuint VAO;
	GLuint VBO;
	GLsizei vertCount;

	void CreateBuffers(GLuint shaderProgram);
};

