#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H
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

class sphere
{
public:

	vector<Vertex> vertices;
	vector<GLuint> indices;
	float radius;
	int rings;
	int sectors;

	sphere(float radius, int rings, int sectors);

	void createSphere();

private:
	void push_indices(int r, int s);

};

#endif#pragma once
