#include"sphere.h"


sphere::sphere(float Radius, int Rings, int Sectors)
{
	radius = Radius;
	rings = Rings;
	sectors = Sectors;
}


void sphere::createSphere()
{
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);
    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            float const y = sin(-glm::half_pi<float>() + glm::pi<float>() * r * R);
            float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
            float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
            vertices.push_back(Vertex{ glm::vec3(x, y, z) * radius, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(s * S, r * R) });
            push_indices(r,s);
        }
    }
}




void sphere::push_indices(int r,int s)
{
    int curRow = r* sectors;
    int nextRow = (r + 1) * sectors;
    indices.push_back(curRow + s);
    indices.push_back(nextRow + s);
    indices.push_back(nextRow + (s + 1));
    indices.push_back(curRow + s);
    indices.push_back(nextRow + (s + 1));
    indices.push_back(curRow + (s + 1));
}