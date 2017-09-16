#ifndef CAMERAIF__
#define CAMERAIF__

#include <iostream>
#include <string>
// GLEW
#include "../../__libs/glew-1.13.0/include/GL/glew.h"
// GLM
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"
// ShaderIf
#include "../../Shaders/if/ShaderIf.h"

namespace Camera
{
namespace CameraIf
{
class CameraIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	virtual ~CameraIf()
	{
		std::cout << "CameraIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	virtual glm::vec3 getcameraPosition() { return glm::vec3(1.0f, 1.0f, 1.0f); };
	virtual GLfloat getcameraPositionX()  { return 0; };
	virtual GLfloat getcameraPositionY()  { return 0; };

	//virtual void setcameraPosition(glm::vec3 _position) {};
	virtual void invertCameraDown() {};
	virtual void invertCameraUp() {};
	virtual void setcameraPositionY(GLfloat _positionY) {};

	virtual void moveForward(GLfloat deltaTime) {};
	virtual void moveBack(GLfloat deltaTime) {};
	virtual void strafeLeft(GLfloat deltaTime) {};
	virtual void strafeRight(GLfloat deltaTime) {};

	virtual void camFront(glm::vec3 _cameraFront) {};

	virtual void stopTranslate() {};
	virtual void invertCameraY() {};
	virtual void updateCameraPosition() {};
	virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader) {};
	virtual void updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader) {};
	// OPERATORs		
private:
};
}
}
#endif