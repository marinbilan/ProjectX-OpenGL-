#ifndef MODELIF__
#define MODELIF__

#include <iostream>
#include <string>
#include <vector>
//
// ASSIMP
//
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/Importer.hpp"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/postprocess.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/mesh.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/scene.h"
//
// GLM
//
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"
//
// FreeImage
//
#include "../../__libs/FreeImage/include/FreeImage.h"
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
	// ASSIMP
	//
	virtual void Clear() {};

	virtual bool InitFromScene(const aiScene* pScene, const std::string& Filename) { return false; };
	virtual void InitMesh(unsigned int Index, const aiMesh* paiMesh)               {};
	virtual bool InitMaterials(const aiScene* pScene, const std::string& Filename) { return false; };

	virtual void Render() {};
	//
	//
	//
	// virtual void translateModel() {};
	//
	// OPERATORs
	//			
private:

};
}
}

#endif