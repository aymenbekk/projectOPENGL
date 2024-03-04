#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shader.h"



class Camera
{
public:

	glm::vec3 Position;
	glm::vec3 TargetPoint = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec3 Right;

	bool firstClick = true;


	int width;
	int height;



	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float lastX = 400.0f;
	float lastY = 400.0f;
	float speed;
	float sensitivity = 0.1f;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame


	Camera( glm::vec3 position,int width,int height);




	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

	void Inputs(GLFWwindow* window);

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void updateCameraVectors();

	void ProcessMouseMovement( double xposIn, double yposIn, GLboolean constrainPitch );


};
#endif