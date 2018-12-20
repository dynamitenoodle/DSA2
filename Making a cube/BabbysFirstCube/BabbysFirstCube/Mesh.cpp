#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
}

void Mesh::InitWithVertexArray(GLfloat vertexes[], size_t count, GLuint shaderProgram)
{
	this->vertices = vector<GLfloat>(count);
	memcpy(&(this->vertices[0]), vertexes, count * sizeof(GLfloat));

	vertCount = count / 3;
	CreateBuffers(shaderProgram);
}

void Mesh::Render() 
{
	//set VAO and draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}

void Mesh::CreateBuffers(GLuint shaderProgram)
{
	glGenVertexArrays(1, &VAO);	//create 1 VAO and store it
	glBindVertexArray(VAO);		//tells OpenGL that this is our 'array' (descriptor)

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//tells OpenGL that this is our 'array buffer' (memory)
	glBufferData(			//create a 'buffer store' (place to put this memory in GPU)						
		GL_ARRAY_BUFFER,
		sizeof(GLfloat) * 3 * vertCount,	//size
		&(vertices[0]),			//pointer to starting loc
		GL_STATIC_DRAW);	//'hints' at what this will be used for

							//GL_ARRAY_BUFFER msut be bound prior to this call
	GLuint attribIndex = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(
		attribIndex,			//index of attribute
		3,						//count of data
		GL_FLOAT,				//kind of data
		GL_FALSE,				//should data be normalized?
		3 * sizeof(GLfloat),	//stride - how many index to skip ahead to reach more of this data
		(GLvoid*)0);			//offset - how many index to skip to reach first value
	glEnableVertexAttribArray(attribIndex);	//enable what we just did earlier 

											//unbind things
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
