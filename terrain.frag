#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;



in vec3 color;

in vec2 texCoord;

in vec3 pos;

in vec3 cubeColor;




void main()
{
 
 if(pos.y == 1.0f){
 FragColor = vec4(cubeColor,1.0f);
 }
 else{
  FragColor = vec4(0.5f,0.5f,0.5f,1.0f);
 }

	
}