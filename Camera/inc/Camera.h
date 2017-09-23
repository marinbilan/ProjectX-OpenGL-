#ifndef CAMERA__
#define CAMERA__

#include <iostream>
#include <string>
// CameraIf
#include "../if/CameraIf.h"

namespace Camera
{
class Camera : public CameraIf::CameraIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs	
	Camera(glm::vec3 _cameraPos, glm::vec3 _cameraFront, glm::vec3 _cameraUp);

	~Camera();
	// FUNCTIONs
	virtual glm::vec3 getcameraPosition();
	virtual GLfloat getcameraPositionX();
	virtual GLfloat getcameraPositionY();

	//virtual void setcameraPosition(glm::vec3 _position);

	virtual void invertCameraDown();
	virtual void invertCameraUp();
	virtual void setcameraPositionY(GLfloat _positionY);

	virtual void moveForward(GLfloat deltaTime);
	virtual void moveBack(GLfloat deltaTime);
	virtual void strafeLeft(GLfloat deltaTime);
	virtual void strafeRight(GLfloat deltaTime);

	virtual void camFront(glm::vec3 _cameraFront);
	
	virtual void stopTranslate();
	virtual void invertCameraY();
	virtual void updateCameraPosition();
	virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader);
	virtual void updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader);
	//
	// NEW
	//
	virtual glm::mat4 getViewMatrix();
	virtual glm::mat4 getInvViewMatrix();
	virtual void invertCameraMatrix();
	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, Camera& info)
	{
		// Add some info
		return output;
	}
	
private:
	// MODEL VARIABLEs
	glm::mat4 viewMatrix;
	glm::mat4 viewMatrixInv;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront; 
	glm::vec3 cameraUp;

	GLfloat distance;
};
}

#endif
