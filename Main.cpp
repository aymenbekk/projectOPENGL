#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
#include"Mesh.h"
#include "stb/stb_image.h"
#include <cstring>
 

const unsigned int width = 800;
const unsigned int height = 800;
const float maxColor = 256 ;
const float maxHeight = 40;
int rows = 16;
int cols = 16;


std::vector<Vertex> vertices;


std::vector<GLuint> indices;

unsigned char* bytes;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void generateVerticesAndIndices();

float normalize(float original_value, float old_min, float old_max, float new_min, float new_max) {
	return (original_value - old_min) * (new_max - new_min) / (old_max - old_min) + new_min;
}


int main() {

	//Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(width, height, "ProjectPractice", NULL, NULL);
	

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}




	glViewport(0, 0, width, height);



	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	Texture textures[]
	{
		Texture("grass.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("rock.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("snow.jpg", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGB, GL_UNSIGNED_BYTE),
	};








	int width, height, numchanels;
	stbi_set_flip_vertically_on_load(true);

	
	bytes = stbi_load("Heightmap.png", &width, &height, &numchanels, 0);
	generateVerticesAndIndices();



	Shader shaderProgram("shader.vert", "shader.frag");

	vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	
	Mesh floor(vertices, indices, tex);

	
	glEnable(GL_DEPTH_TEST);


	Camera camera(width, height, glm::vec3(0.0f, 10.0f, 20.0f));
	
 
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

	
		/* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
		camera.Inputs(window);


		
		floor.vertices = vertices;
		floor.indices = indices;
		floor.Draw(shaderProgram, camera);


		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}



	shaderProgram.Delete();

	
	glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;

}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
	glViewport(0, 0, width, height);
}

void generateVerticesAndIndices() {

	vertices.clear();
	indices.clear();

	cout << "rows" << rows << "cols" << cols;



	int index = 0;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			//defining squares coords
			float height = static_cast<int>(bytes[i * j]);
			float newHeigh = normalize(height, 0.0f, 223.0f, -1.0f, 1.0f);
		/*	cout << newHeigh << "///";*/
			glm::vec3 position = glm::vec3((-rows / 2.0f) + i, newHeigh, (-cols / 2.0f) + j);
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			float s = i / (rows - 1.0f);
			float t = j / (cols - 1.0f);
			glm::vec2 texUV = glm::vec2(s, t);

			vertices.push_back(Vertex{ position, color,  texUV });



			if (i < rows - 1 && j < cols - 1) {

				//triangle1
				indices.push_back(i * cols + j);
				indices.push_back((i + 1) * cols + j);
				indices.push_back(i * cols + j + 1);

				//triangle2
				indices.push_back((i + 1) * cols + j);
				indices.push_back((i + 1) * cols + j + 1);
				indices.push_back(i * cols + j + 1);
			}
		}
	}

}