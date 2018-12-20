/*
This is the vertex shader
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core

in vec3 position;

uniform mat4 worldMatrix;

//entry point for the fragment shader
void main(void)
{
	gl_Position = vec4(position.x - 0.1, position.y, position.z, 1.0);
}
