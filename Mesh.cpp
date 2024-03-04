#include "Mesh.h"
#include <string> 
using namespace std;
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	
	VBO VBO(vertices);
	
	EBO EBO(indices);
	

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float)));
	

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string myString = "texture";
		textures[i].texUnit(shader, (myString + std::to_string(i + 1)).c_str(), i);
		glActiveTexture(textures[i].Unit);
		textures[i].Bind();
	}


	camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::AttachTransformMatrices(vector<glm::mat4> matrices,vector<glm::vec3> colors) {
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4),matrices.data(), GL_STATIC_DRAW);
	VAO.Bind();
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glBindVertexArray(0);

	//for colors
	unsigned int bufferColors;
	glGenBuffers(1, &bufferColors);
	glBindBuffer(GL_ARRAY_BUFFER, bufferColors);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
	VAO.Bind();
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glVertexAttribDivisor(7, 1);
	glBindVertexArray(0);


}

void Mesh::drawInstances(Shader& shader, Camera& camera ,unsigned int indicesSize,int countCubes) {

	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();




	camera.Matrix(60.0f, 0.01f, 100.0f, shader, "camMatrix");

	
	glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indicesSize), GL_UNSIGNED_INT, 0, countCubes);
}