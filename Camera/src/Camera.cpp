#include <iostream>
#include <string>

#include "../../Camera/inc/Camera.h"
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Camera::Camera::Camera()
{
	//
	// INITIALIZE CAMERA POSITION
	//
	cameraPos =   glm::vec3(0.0f, 15.0f, 15.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp =    glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera::~Camera()
{
	std::cout << "Camera destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Camera::Camera::moveForward(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::Camera::moveBack(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::Camera::strafeLeft(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Camera::strafeRight(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Camera::camFront(glm::vec3 _cameraFront)
{
	cameraFront = _cameraFront;
}

void Camera::Camera::stopTranslate()
{
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
}

void Camera::Camera::updateCameraPosition()
{
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::Camera::updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader)
{
	glUniformMatrix4fv(shader->getViewMatrixID(), 1, GL_FALSE, &viewMatrix[0][0]);
}


