#include"Camera.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <string>

Camera::Camera( glm::vec3 position,int widthh,int heightt)
{
	width = widthh;
	height = heightt;
	Position = position;

}



void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	view = glm::lookAt(Position, TargetPoint, Up);
	// this is the standard its doesnt change)
	projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}



void Camera::Inputs(GLFWwindow* window)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	speed = deltaTime * 2.5f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position.z -= speed;
		TargetPoint.z -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position.x -= speed;
		TargetPoint.x -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position.z += speed;
		TargetPoint.z += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position.x += speed;
		TargetPoint.x += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position.y += speed;
		TargetPoint.y += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position.y -= speed;
		TargetPoint.y -= speed;
	}


}


void Camera::ProcessMouseMovement(float xpos, float ypos, GLboolean constrainPitch ) {
	// Hides mouse cursor
	


	if (firstClick)
	{
		lastX = xpos;
		lastY = ypos;
		firstClick = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	TargetPoint = glm::normalize(direction);
}




	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 





//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//	{
//		
//		// Hides mouse cursor
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//		// Prevents camera from jumping on the first click
//		if (firstClick)
//		{
//			glfwSetCursorPos(window, (width / 2), (height / 2));
//			firstClick = false;
//		}
//
//		// Stores the coordinates of the cursor
//		double mouseX;
//		double mouseY;
//		// Fetches the coordinates of the cursor
//		glfwGetCursorPos(window, &mouseX, &mouseY);
//
//		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
//		// and then "transforms" them into degrees 
//		std::cout << mouseX << "//" << mouseY<<std::endl;
//		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
//		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
//
//		// Calculates upcoming vertical change in the Orientation
//		glm::vec3 newTargetPoint = glm::rotate(TargetPoint, glm::radians(-rotX), glm::normalize(glm::cross(TargetPoint, Up)));
//		std::cout << newTargetPoint.x<<"//" << newTargetPoint.y<<"//" << newTargetPoint.z << std::endl;
//		// Decides whether or not the next vertical Orientation is legal or not
//		if (abs(glm::angle(newTargetPoint, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
//		{
//			TargetPoint = newTargetPoint;
//		}
//
//		// Rotates the Orientation left and right
//		TargetPoint = glm::rotate(TargetPoint, glm::radians(-rotY), Up);
//
//		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
//		glfwSetCursorPos(window, (width / 2), (height / 2));
//	}
//	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
//	{
//		// Unhides cursor since camera is not looking around anymore
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//		// Makes sure the next time the camera looks around it doesn't jump
//		firstClick = true;
//	}
//}




