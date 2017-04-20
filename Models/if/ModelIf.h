#ifndef MODELIF__
#define MODELIF__

#include <iostream>
#include <sstream>
#include <fstream>
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
// Texturef
//
#include "../../Textures/if/TextureIf.h"
#include "../../Loader/inc/ModelLoader.h"
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
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	//
	virtual ~ModelsIf()
	{
		std::cout << "ModelsIf destructor called!" << std::endl;
	}
	//
	// FUNCTIONs
	//
	virtual void VertexAttribPointers() {};
	// SET
	virtual void setModelScale() {};
	virtual void setModelRotation() {};
	virtual void setModelPosition(glm::vec3 _modelPosition) {};
	// GET
	virtual GLuint getNumberOfMeshes() { return 0; };

	virtual glm::vec3 getModelScale()    { return dummyVec3; };
	virtual glm::vec3 getModelRotation() { return dummyVec3; };
	virtual glm::vec3 getModelPosition() { return dummyVec3; };
	//
	// ASSIMP
	//
	virtual bool initFromScene(const aiScene* _pScene)           { return false; };
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh) { };

	virtual void render() {};
	//
	// OPERATORs
	//			
private:
	// DUMMY RETURN
	glm::vec3 dummyVec3;
};
}
}

#endif