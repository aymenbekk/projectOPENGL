#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

out vec3 pos;


uniform mat4 camMatrix;



void main()
{
	
	
	color = aColor;
	
	texCoord = aTex;
	
	
	gl_Position = camMatrix * vec4(aPos, 1.0);
	pos=aPos;
}