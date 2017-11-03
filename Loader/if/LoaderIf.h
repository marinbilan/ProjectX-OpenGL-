#ifndef LOADERIF__
#define LOADERIF__

#include "../../CommonFunctions/CommonFunctions.h"
//
//                          LoaderIf 
//                          [struct Mesh] // Shared between ModelLoaderLearningOpenGL and TextureLoader
//                          ----------
//                             |
//       --------------------------------------------------
//       |                     |                          |
//  ModelLoader     [ ModelLoaderLearningOpenGL ]    [ TextureLoader ]
//                  [ struct Vert]

namespace Loader
{
struct Mesh
{
	GLuint VBO;
	GLuint IBO;
	GLuint numIndices; // = number of vertices
	GLfloat meshSizeMB;

	GLuint  texture0ID;
	GLuint textureNormalMap0ID;
	// Texture params
	GLuint  textureWidth;
	GLuint  textureHeight;
	GLfloat textureSizeMB;
};

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
	virtual void loadModelPTN()                                   {};
	virtual void initScene(const aiScene* _pScene)                {};
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh)  {};
	// GET
	virtual GLuint getModelVAO()                                  { return 0; };
	virtual std::vector<Loader::Mesh> getVectorOfMeshes()         { return std::vector<Loader::Mesh>(); };
	// SET
	// TEXTUREs
	virtual void loadTModelPTNTextures() {};
	virtual GLuint createSingleTexture(GLuint& _textureWidth, GLuint& _textureHeight, GLfloat& _textureSize, std::string& _textureName) { return 0; };
	
	virtual GLuint createSingleTexture(std::string& _textureName) { return 0; };
	// GET
	// SET
	virtual void setTextureForEachMesh()                          {};
private:
};
}
}
#endif