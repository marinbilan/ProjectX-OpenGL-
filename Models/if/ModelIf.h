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
	virtual void VertexAttribPointers() {}
	// SET
	virtual void setModelPosition(glm::vec3 _modelPosition) {}
	virtual void setModelScale() {}
	virtual void setModelRotation() {}
	// GET
	virtual glm::vec3 getModelPosition() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelScale()    { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelRotation() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual GLuint getModelAngle()       { return 0; };
	// RENDER
	virtual void render() {};
	virtual void renderDepth(Shaders::ShadersIf::ShadersIf* _shader) {};
	// OPERATORs		
private:
	// DUMMY RETURN
};
}
}
#endif