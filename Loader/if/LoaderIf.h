#ifndef LOADERIF__
#define LOADERIF__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "..\..\__libs\glew-1.13.0\include\GL\glew.h"

#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/Importer.hpp"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/postprocess.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/mesh.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/scene.h"

#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"

#include "../../__libs/FreeImage/include/FreeImage.h"

namespace Loader
{
namespace LoaderIf
{
class LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] TexturesIf() {}
	virtual ~LoaderIf()
	{
		std::cout << "LoaderIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	// MODEL
	virtual bool initFromScene(const aiScene* _pScene)                                     { return false; };
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh)                           {};
	virtual GLuint getNumberOfMeshes()                                                     { return 0; };
	// TEXTUREs
	virtual void loadSingleTexture2DID(char* _textureName) {};
	virtual void loadVectorOfTextures2DID()                {};
	virtual GLuint getSingleTexture2DID()                  { return 0; };
	virtual std::vector<GLuint> getVectorOfTextures2DID()  { return dummyReturn; };
private:
	std::vector<GLuint> dummyReturn;
};
}
}
#endif