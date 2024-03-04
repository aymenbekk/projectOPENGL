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
#include "Terrain.hpp"
#include "sphere.h"
const unsigned int ScrWidth = 800;
const unsigned int ScrHeight = 800;
const float maxColor = 256 ;
const float maxHeight = 40;
const int rows = 16;
const int cols = 16;


std::vector<Vertex> vertices;


std::vector<GLuint> indices;

vector<glm::vec3> faceNormals;

vector<float> normals;

vector <int> adjacentFace[rows*cols];
vector<vector<int>> s;
unsigned char* bytes;
glm::vec3 camPos = glm::vec3(0.0f, 7.0f, 15.0f);
Camera camera(camPos,ScrWidth,ScrHeight);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void generateVerticesAndIndices();
//glm::vec2 getMaxMin();

float normalize(float original_value, float old_min, float old_max) {
	return (2*(original_value-old_min))/(old_max-old_min)-1;
}

void calculateNormals();
vector<int> searchForAdjacentFaces(int vertexIndex);
void drawNormals();

int main() {

	//Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(ScrWidth, ScrWidth, "ProjectPractice", NULL, NULL);
	

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




	glViewport(0, 0, ScrWidth, ScrHeight);



	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	glfwSetCursorPosCallback(window, mouse_callback);





	int width, height, numchanels;
	stbi_set_flip_vertically_on_load(true);

	
	bytes = stbi_load("Heightmap.png", &width, &height, &numchanels, 0);
	generateVerticesAndIndices();


	glm::vec3 surfacePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 surfaceModel = glm::mat4(1.0f);
	surfaceModel = glm::translate(surfaceModel, surfacePos);

	Shader terrainShader("terrain.vert", "terrain.frag");
	terrainShader.Activate();

	vector <Texture> textures;
	textures.push_back(Texture("grass.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE));
	textures.push_back(Texture("rock.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE));
	textures.push_back(Texture("snow.jpg", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGB, GL_UNSIGNED_BYTE));

	vector <Texture> textures2;


	//glm::vec4 lightColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//defining a model matrix to position our cube in the scene/world
	glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, -1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	Shader shaderLight("light.vert", "light.frag");
	shaderLight.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderLight.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(shaderLight.ID, "lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
	//firstFloor
	Shader shaderProgram("shader.vert", "shader.frag");
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(surfaceModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camPos.x, camPos.y, camPos.z);

	Mesh floor(vertices, indices, textures);



	sphere sphere(1.0f, 20, 30);
	sphere.createSphere();

	Mesh sphereMesh(sphere.vertices, sphere.indices, textures2);
	//terrain
	Terrain terrain(800, 20);
	terrain.generateTerrain();

	
	glEnable(GL_DEPTH_TEST);

	generateVerticesAndIndices();
	
	cout << "vertice" << "first" << vertices[0].normal.x << "/" << vertices[0].normal.y << "/" << vertices[0].normal.z << "/" << endl;
	cout << "vertice" << "first" << vertices[1].normal.x << "/" << vertices[1].normal.y << "/" << vertices[1].normal.z << "/" << endl;
	// Main while loop


	drawNormals();
	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;
	while (!glfwWindowShouldClose(window))
	{

		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0) {
			string FPS = to_string((1.0 / timeDiff) * counter);
			string title = "project - " + FPS;
			glfwSetWindowTitle(window, title.c_str());
			prevTime = crntTime;
			counter = 0;

		}


		processInput(window);

	/*
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//this draws the normals
		/*glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, normals.size()/3);*/

		camera.Inputs(window);

		//sphereMesh.Draw(shaderLight, camera);
		floor.vertices = vertices;
		floor.indices = indices;
	/*	floor.Draw(shaderProgram, camera);*/
		
		terrain.drawTerrain(terrainShader, camera);

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}



	terrainShader.Delete();

	
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
	camera.width = width;
	camera.height = height;
}

void generateVerticesAndIndices() {

	vertices.clear();
	indices.clear();


	//glm::vec2 MaxMin = getMaxMin();
	//cout << "max:" << MaxMin.x << "Min :" << MaxMin.y;

	int index = 0;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			//defining squares coords
			float height = static_cast<int>(bytes[i * j]);
			float newHeigh = normalize(height, 0.0f, 254.0f);
		/*	cout << newHeigh << "///";*/
			//first loop to traverse rows and second for columns (the axe X is columns and Z is rows)
			glm::vec3 position = glm::vec3((-rows / 2.0f) + j, newHeigh*2.0f, (-cols / 2.0f) + i);
			
		
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			float s = j / (rows - 1.0f);
			float t = i / (cols - 1.0f);
			glm::vec2 texUV = glm::vec2(s, t);
			
			vertices.push_back(Vertex{ position, color,  texUV});



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

	for (int i = 0; i < indices.size(); i += 3) {

		glm::vec3 V1 = vertices[indices[i + 1]].position - vertices[indices[i]].position;
		glm::vec3 V2 = vertices[indices[i + 2]].position - vertices[indices[i]].position;
		glm::vec3 crossProduct = glm::cross(V1,V2);
		faceNormals.push_back(normalize(crossProduct));


		adjacentFace[indices[i]].push_back(i / 3);
		adjacentFace[indices[i + 1]].push_back(i / 3);
		adjacentFace[indices[i + 2]].push_back(i / 3);

	}
	

	for (int i = 0; i < vertices.size(); i++) {

		vector<int> facesIndices = adjacentFace[i];
		glm::vec3 vertexNormal = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int j = 0; j < facesIndices.size(); j++) {
			vertexNormal += faceNormals[j];
		}
		glm::vec3 normalized = normalize(glm::vec3(vertexNormal.x , vertexNormal.y , vertexNormal.z ));
		vertices[i].normal.x = normalized.x;
		vertices[i].normal.y = normalized.y;
		vertices[i].normal.z = normalized.z;
		/*	cout << "vertice"<<i<<vertices[i].normal.x << "/" << vertices[i].normal.y << "/" << vertices[i].normal.z << "/" << endl;*/
	}


}

void calculateNormals() {
	
	

}



void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	camera.ProcessMouseMovement(xpos, ypos,true);
}



void drawNormals() {
	
	float normal_length = 5.0;
	//this assumes your mesh has 2 arrays of the same length
	//containing structs of vertices and normals
	for (int i = 0; i < vertices.size(); i++) {
		//retrieving the normal associated with this vertex
		float nx = vertices[i].normal.x;
		float ny = vertices[i].normal.y;
		float nz = vertices[i].normal.z;

		//retrieving the vertex itself, it'll be the first point of our line
		float v1x = vertices[i].position.x;
		float v1y = vertices[i].position.y;
		float v1z = vertices[i].position.z;

		//second point of our line representing the normal direction
		float v2x = v1x + nx * normal_length;
		float v2y = v1y + ny * normal_length;
		float v2z = v1z + nz * normal_length;

		
		normals.push_back(v1x); 
		normals.push_back(v1y);
		normals.push_back(v1z);
		normals.push_back(v2x);
		normals.push_back(v2y);
		normals.push_back(v2z);


	}

	

}

void drawNormalsFinal() {

}