#ifndef CAMERAIF__
#define CAMERAIF__

#include <iostream>
#include <string>

#include "../../__libs/glew-1.13.0/include/GL/glew.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
//
// ShaderIf
//
#include "../../Shaders/if/ShaderIf.h"

namespace Camera
{
namespace CameraIf
{
class CameraIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	//
	virtual ~CameraIf()
	{
		std::cout << "CameraIf destructor called!" << std::endl;
	}
	//
	// FUNCTIONs
	//
	virtual void moveForward(GLfloat deltaTime) {};
	virtual void moveBack(GLfloat deltaTime) {};
	virtual void strafeLeft(GLfloat deltaTime) {};
	virtual void strafeRight(GLfloat deltaTime) {};

	virtual void camFront(glm::vec3 _cameraFront) {};

	virtual void stopTranslate() {};
	virtual void updateCameraPosition() {};
	virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader) {};
	//
	// OPERATORs
	//			
private:

};
}
}

#endif