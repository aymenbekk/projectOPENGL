#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 textUV;
layout (location=3 ) in mat4 TransformCube;
layout (location=7 ) in vec3 color;


uniform mat4 camMatrix;

out vec3 cubeColor;
out vec3 pos;


void main()
{
	gl_Position = camMatrix  * TransformCube * vec4(aPos, 1.0f);
	cubeColor=color;
	pos=aPos;
}