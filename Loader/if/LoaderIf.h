#pragma once

#include "../../CommonFunctions/CommonFunctions.h"
//
//                          LoaderIf 
//                          [struct Mesh] // Shared between ModelLoaderLearningOpenGL and TextureLoader
//                          ----------
//                             |
//       --------------------------------------------------
//       |                     |                          |
//  ModelLoader     [ ModelLoaderLearningOpenGL ]    [ TextureLoader ]
//                  [ struct Vert ]

namespace Loader
{
struct Mesh
{
	GLuint VBO;
	GLuint IBO;
	GLuint numIndices; // = number of vertices
	GLfloat meshSizeMB;

	// Texture params
	GLuint texture0ID;
	GLuint  textureWidth;
	GLuint  textureHeight;
	GLfloat textureSizeMB;
	// Texture Specular Map params
	GLuint  textureSpecularMap0ID;
	GLuint  textureSpecularlMapWidth;
	GLuint  textureSpecularMapHeight;
	GLfloat textureSpecularlMapSizeMB;
	// Texture Normal Map params
	GLuint  textureNormalMap0ID;
	GLuint  textureNormalMapWidth;
	GLuint  textureNormalMapHeight;
	GLfloat textureNormalMapSizeMB;
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
	virtual void loadModelPTN()                                  {};
	virtual void initScene(const aiScene* _pScene)               {};
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh) {};
	// GET
	virtual GLuint getModelVAO()                                 { return 0; };
	virtual std::vector<Loader::Mesh> getVectorOfMeshes()        { return std::vector<Loader::Mesh>(); };
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