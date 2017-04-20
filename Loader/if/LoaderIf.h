#ifndef LOADERIF__
#define LOADERIF__

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
//
// ShaderIf
//
#include "../../Shaders/if/ShaderIf.h"
//
// CameraIf
//
#include "../../Camera/if/CameraIf.h"

namespace Loader
{
namespace LoaderIf
{
class LoaderIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] TexturesIf() {}
	//
	virtual ~LoaderIf()
	{
		std::cout << "LoaderIf destructor called!" << std::endl;
	}
	//
	// FUNCTIONs
	//
	// TEXTUREs
	virtual GLuint loadTexture2DID(std::string& _textureName)                                              { return 0; }
	virtual std::vector<GLuint> loadtexture2DVectorIDs(char* _textureFolderPath, GLuint _numberOfTextures) { return dummyReturn; }
	// MODEL
	virtual bool initFromScene(const aiScene* _pScene)                                                     { return false; };
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh)                                           {};
	// GET
	virtual GLuint getNumberOfMeshes() { return 0; };
private:
	std::vector<GLuint> dummyReturn;
};
}
}

#endif