#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;



in vec3 color;

in vec2 texCoord;

in vec3 pos;


// Gets the Texture Units from the main function
uniform sampler2D texture1;

uniform sampler2D texture2;

uniform sampler2D texture3;





void main()
{
	// outputs final color
	if(pos.y >= 0.7){
	FragColor = texture(texture3,texCoord);
	}
	else if(pos.y > 0.4){
	FragColor = texture(texture2,texCoord);
	}
	else if(pos.y <=  0.4){
	FragColor = texture(texture1,texCoord);
	}
	
}