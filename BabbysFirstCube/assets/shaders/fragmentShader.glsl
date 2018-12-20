/*
This is the fragment shader, and it's main job is to determine the color for each pixel (fragment)
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core

//entry point for the fragment shader
void main(void)
{
	// sets the output (color)
	gl_FragColor = vec4(1, 0, 1, 1);
}