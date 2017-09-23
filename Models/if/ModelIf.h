#ifndef MODELIF__
#define MODELIF__

#include <iostream>
#include <string>
#include <vector>
// GLM
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"
// Loader
#include "../../Loader/inc/ModelLoader.h"
#include "../../Loader/inc/TextureLoader.h"
// ShaderIf
#include "../../Shaders/if/ShaderIf.h"
// CameraIf
#include "../../Camera/if/CameraIf.h"

namespace Models
{
namespace ModelsIf
{
class ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	virtual ~ModelsIf()
	{
		std::cout << "ModelsIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	// SET
	virtual void setModelPosition(glm::vec3 _modelPosition)                     {}
	virtual void setModelScale(glm::vec3 _modelScale)                           {}
	virtual void setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle) {}
	// GET
	virtual GLuint getModelVAO() { return 0; };

	virtual std::vector<GLuint> getVectorOfVBOs()          { return dummyVec; }
	virtual std::vector<GLuint> getVectorOfIBOs()          { return dummyVec; }
	virtual std::vector<GLuint> getTexturesVectorId()      { return dummyVec; }
	virtual std::vector<GLuint> getNumberOfIndicesVector() { return dummyVec; }
	virtual GLuint getNumOfMeshes()                        { return 0; };

	virtual glm::mat4 getModelMatrix()   { return  dummyMat4x4; }
	virtual glm::vec3 getModelPosition() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelScale()    { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelRotation() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual GLfloat   getModelAngle()    { return 0; };
	// RENDER
	virtual void render() {};
	virtual void renderDepth(Shaders::ShadersIf::ShadersIf* _shader) {};
	// OPERATORs		
private:
	// DUMMY RETURN
	std::vector<GLuint> dummyVec;
	glm::mat4 dummyMat4x4;
};
}
}
#endif