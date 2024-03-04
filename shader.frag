#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;



in vec3 color;

in vec2 texCoord;

in vec3 pos;

in vec3 crntPos;

in vec3 Normal;

// Gets the Texture Units from the main function
uniform sampler2D texture1;

uniform sampler2D texture2;

uniform sampler2D texture3;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

void main()
{

    float ambient = 0.20f;

    vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuse = max(dot(Normal,lightDirection),0.0f);


	float specularLight= 0.5f;
	vec3 viewDirection= normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection,Normal);
	float speculAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8);
	float specular = speculAmount * specularLight;


	// outputs final color
	if(pos.y >= 0.7){
	FragColor = texture(texture3,texCoord)*lightColor*(diffuse + ambient + specular );
	}
	else if(pos.y > 0.4){
	FragColor = texture(texture2,texCoord)*lightColor*(diffuse + ambient + specular );
	}
	else if(pos.y <=  0.4){
	FragColor = texture(texture1,texCoord)*lightColor*(diffuse + ambient + specular );
	}
	
}