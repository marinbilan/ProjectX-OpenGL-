#pragma once
#include "../../CommonFunctions/CommonFunctions.h"
//                          LoaderIf 
//                          [struct Mesh] // Shared between ModelLoaderLearningOpenGL and TextureLoader
//                          -------------
//                             |
//       +---------------------+--------------------------+
//       |                     |                          |
//  ModelLoader     [ ModelLoaderLearningOpenGL ]    [ TextureLoader ]
//                  [ struct Vert ]
//                  [ struct VertNormalMap ]

namespace Loader
{
struct Mesh
{
	// Model Loader Part
	GLuint VBO;
	GLuint IBO;
	// # of vertices = # of indices
	GLuint numIndices;
	// Shader
	// Texture Loader Part
	GLuint texture0ID;
	GLuint textureSpecularMap0ID;
	GLuint textureNormalMap0ID;
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
	// initialization
	virtual void loadModelPTN()                                           {}
	virtual void initScene(const aiScene* _pScene)                        {}
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh)          {}
	virtual void initNormalMapMesh(GLuint _index, const aiMesh* _paiMesh) {}
	// GET
	virtual GLuint                     getModelVAO()              { return 0; }
	virtual std::vector<Loader::Mesh>& getVectorOfMeshes()        { return std::vector<Loader::Mesh>(); }
	// SET

	// TEXTUREs
	virtual void   loadTModelPTNTextures() {};	
	virtual GLuint createSingleTexture(std::string& _textureName) { return 0; }
	// GET
	// SET
	virtual void setTextureForEachMesh() {}
private:
};
}
}