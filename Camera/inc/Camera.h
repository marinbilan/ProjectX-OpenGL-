#ifndef CAMERA__
#define CAMERA__

#include <iostream>
#include <string>
//
// CameraIf
//
#include "../if/CameraIf.h"

namespace Camera
{
class Camera : public CameraIf::CameraIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Camera();

	~Camera();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual void moveForward(GLfloat deltaTime);
	virtual void moveBack(GLfloat deltaTime);
	virtual void strafeLeft(GLfloat deltaTime);
	virtual void strafeRight(GLfloat deltaTime);

	virtual void camFront(glm::vec3 _cameraFront);
	
	virtual void stopTranslate();
	virtual void updateCameraPosition();
	virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader);
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Camera& info)
	{
		// Add some info
		return output;
	}
	
private:
	//
	// MODEL VARIABLEs
	//
	glm::mat4 viewMatrix;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront; 
	glm::vec3 cameraUp;
};
}

#endif
