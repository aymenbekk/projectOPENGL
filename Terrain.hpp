#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
#include"Mesh.h"
#include <cstring>

class Terrain
{
public:

    int size;
    int countVertices;
    vector<Vertex> vertices;
    vector<GLuint> indices;
	Mesh* cubeMesh;


private:

	vector<Vertex> cubeVertices;
	vector<GLuint> cubeIndices;
	vector<glm::mat4> matrices;
	vector<glm::vec3> colors;
	unsigned char* bytes;

public:
    // constructor with vectors
    Terrain(int sizee, int verticess)
    { size = sizee;
      countVertices = verticess;
    }
    


	void generateTerrain() {
		vector<Texture> textures;
		textures.push_back(Texture("grass.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE));
		generateCube();
		cubeMesh=new Mesh(cubeVertices, cubeIndices, textures);
		generateTransformMatrices();
		


	}

	void drawTerrain(Shader& shader, Camera& camera) {

		//andColors
		cubeMesh->AttachTransformMatrices(matrices,colors);
	
		cubeMesh->drawInstances(shader, camera, cubeIndices.size(), pow(countVertices, 2));
	}



    void generate() {
		int k = 0;
		for (int i = 0; i < countVertices; ++i) {
			for (int j = 0; j < countVertices; ++j) {
				//defining cubes coords
			
					//first loop to traverse rows and second for columns (the axe X is columns and Z is rows)
				glm::vec3 topPoint = glm::vec3((-countVertices / 2.0f) + j, 0.0f, (-countVertices / 2.0f) + i);
				glm::vec3 BottomPoint = glm::vec3((-countVertices / 2.0f) + j, -1.0f, (-countVertices / 2.0f) + i);

				glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
				/*float s = j / (rows - 1.0f);
				float t = i / (cols - 1.0f);
				glm::vec2 texUV = glm::vec2(s, t);*/
				vertices.push_back(Vertex{ topPoint, color,  glm::vec2(0.0f,0.0f)});
				vertices.push_back(Vertex{ BottomPoint, color,  glm::vec2(0.0f,0.0f) });

				

				if (i < countVertices - 1 && j < countVertices - 1) {
					cout << "dkhalna : " << k++ << endl;
					//rectangle top
					//triangle1
					indices.push_back((i * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2);
					indices.push_back((i * countVertices + j + 1) * 2);

					//triangle2
					indices.push_back(((i + 1) * countVertices + j) * 2);
					indices.push_back((i * countVertices + j + 1) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 2);



					//rectangle bottom
					//triangle3
					indices.push_back((i * countVertices + j) * 2 + 1);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 1);
					indices.push_back((i * countVertices + j + 1) * 2 + 1);

					//triangle4
					indices.push_back(((i + 1) * countVertices + j) * 2 + 1);
					indices.push_back((i * countVertices + j + 1) * 2 + 1);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 3);

					//all you need to do is take the already found indexes above and mixe them to find the rest of the triangles

					indices.push_back((i * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 1);

					////triangle2
					indices.push_back((i * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 1);
					indices.push_back((i * countVertices + j) * 2 + 1);

					////rectangle bottom
					////triangle3
					indices.push_back((i * countVertices + j + 1) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 3);

					////triangle4
					indices.push_back((i * countVertices + j + 1) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 3);
					indices.push_back((i * countVertices + j + 1) * 2 + 1);


					indices.push_back(((i + 1) * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 3);

					indices.push_back(((i + 1) * countVertices + j) * 2);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 3);
					indices.push_back(((i + 1) * countVertices + j) * 2 + 1);

					indices.push_back((i * countVertices + j) * 2);
					indices.push_back((i * countVertices + j + 1) * 2);
					indices.push_back((i * countVertices + j + 1) * 2 + 1);

					indices.push_back((i * countVertices + j) * 2);
					indices.push_back((i * countVertices + j + 1) * 2 + 1);
					indices.push_back((i * countVertices + j) * 2 + 1);

				}
				}
			}
		}


	private:

		void generateCube() {
	
			cubeVertices.push_back(Vertex{ glm::vec3(0.5f,0.0f,-0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(0.5f,0.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(-0.5f,0.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(-0.5f,0.0f,-0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(0.5f,1.0f,-0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(0.5f,1.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(-0.5f,1.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });
			cubeVertices.push_back(Vertex{ glm::vec3(-0.5f,1.0f,-0.5f),glm::vec3(1.0f,1.0f,1.0f),glm::vec2() });


			cubeIndices = {
				0,1,2,
				0,2,3,
				4,5,6,
				4,6,7,
				1,2,6,
				1,5,6,
				0,4,7,
				0,3,7,
				1,0,4,
				1,5,4,
				2,3,7,
				2,6,7
			};
		}

		//andColors
		void generateTransformMatrices() {
			int width, height, numchanels;
			stbi_set_flip_vertically_on_load(true);


			bytes = stbi_load("Heightmap.png", &width, &height, &numchanels, 0);
			bool switchColor = false;
			bool nextRow = false;
			std::cout << "generation of matrices"<< std::endl;
			for (int i = -countVertices/2 ; i < countVertices/2; i += 1) {
				for (int j = -countVertices/2 ; j < countVertices/2 ; j += 1) {

					float height = static_cast<int>(bytes[i * j]);
					float newHeigh = std::floor(normalize(height, 0.0f, 223.0f, 0.0f, 10.0f));

					glm::mat4 model = glm::mat4(1.0f);
					
					float x = static_cast<float>(j) ;
					float z = static_cast<float>(i) ;
					model = glm::translate(model, glm::vec3(x, 0.0f,z));
					matrices.push_back(model);
					if (nextRow == false) {
						if (switchColor == false) {
							colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
							switchColor = true;
						}
						else {
							colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
							switchColor = false;
						}
					}
					else {
					
						if (switchColor == false) {
							
							colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
							switchColor = true;
						}
						else {
							colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
							switchColor = false;
						}
					}
				
				}
				if (nextRow == false) {
					nextRow = true;
				}
				else {
					nextRow = false;
				}
			}
			std::cout << "done" << std::endl;
			
		}

		void printMat4(const glm::mat4& matrix) {
			for (int row = 0; row < 4; ++row) {
				for (int col = 0; col < 4; ++col) {
					std::cout << matrix[row][col] << "\t";
				}
				std::cout << std::endl;
			}
		}

		void printMatrices() {
			cout << "matrices size : " << matrices.size() << endl;
			for (size_t i = 0; i < matrices.size(); ++i) {
				std::cout << "Matrix " << i + 1 << ":" << std::endl;

				// Print each row of the matrix
				for (int row = 0; row < 4; ++row) {
					for (int col = 0; col < 4; ++col) {
						std::cout << matrices[i][row][col] << "\t";
					}
					std::cout << std::endl;
				}

				std::cout << std::endl;
			}
		}

		float normalize(float original_value, float old_min, float old_max, float new_min, float new_max) {
			return (original_value - old_min) * (new_max - new_min) / (old_max - old_min) + new_min;
		}



    
};

#endif




