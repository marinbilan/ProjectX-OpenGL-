#ifndef MODELIF__
#define MODELIF__

#include <iostream>
#include <string>

#include "../../__libs/glew-1.13.0/include/GL/glew.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"

#include "../FreeImage/include/FreeImage.h"
//
// ShaderIf
//
#include "../../Shaders/if/ShaderIf.h"
//
// CameraIf
//
#include "../../Camera/if/CameraIf.h"

namespace Models
{
namespace ModelsIf
{
class ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	//
	//
	virtual ~ModelsIf()
	{
		std::cout << "ModelsIf destructor called!" << std::endl;
	}
	//
	//
	// FUNCTIONs
	//
	//
	virtual void VertexAttribPointers() {};

	virtual void renderModel() {};
	//
	// OPERATORs
	//			
private:

};
}
}

#endif