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
	cameraPos =   glm::vec3(0.0f, 0.0f, 15.0f);
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
glm::vec3 Camera::Camera::getcameraPosition()
{
	return cameraPos;
}

GLfloat Camera::Camera::getcameraPositionX()
{
	return cameraPos.x;
}

GLfloat Camera::Camera::getcameraPositionY()
{
	return cameraPos.y;
}

//void Camera::Camera::setcameraPosition(glm::vec3 _position)
//{
//	cameraPos = _position;
//}
//
void Camera::Camera::setcameraPositionY(GLfloat _positionY)
{
	cameraPos.y = _positionY;
}

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

void Camera::Camera::invertCameraY()
{
	cameraFront.y = -cameraFront.y;
}

void Camera::Camera::updateCameraPosition()
{
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::Camera::updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader)
{
	glUniformMatrix4fv(shader->getViewMatrixID(), 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 viewMatrixInv = glm::inverse(viewMatrix);
	glUniformMatrix4fv(shader->getViewMatrixInvID(), 1, GL_FALSE, &viewMatrixInv[0][0]);
}

void Camera::Camera::updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader)
{
	glUniformMatrix4fv(shader->getViewMatrixID(), 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 viewMatrixInv = glm::inverse(viewMatrix);
	glUniformMatrix4fv(shader->getViewMatrixInvID(), 1, GL_FALSE, &viewMatrixInv[0][0]);
}


