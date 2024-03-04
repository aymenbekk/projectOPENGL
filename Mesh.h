#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;


	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	
	void Draw(Shader& shader, Camera& camera);
	void AttachTransformMatrices(std::vector<glm::mat4> matrices, std::vector<glm::vec3> colors);

	void drawInstances(Shader& shader, Camera& camera,unsigned int indicesSize, int countCubes);
};
#endif