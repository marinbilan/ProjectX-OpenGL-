#pragma once
#include "../if/LoaderIf.h"

namespace Loader
{
class TextureLoader : public LoaderIf::LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	TextureLoader(CommonFunctions& _CF, 
		          char*  _modelFolder,
		          GLuint _numberOfTextures);
	~TextureLoader();

	// FUNCTIONs
	void loadTModelPTNTextures();
	GLuint createSingleTexture(std::string& _textureName);
	// GET
	std::vector<Loader::Mesh>& getVectorOfMeshes();
	// SET
	void setTextureForEachMesh();

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, TextureLoader& info)
	{
		return output;
	}

private:
	GLuint textureID;

	char*  modelFolder;
	GLuint numberOfTextures;

	std::vector<Mesh> vectorOfMeshes;

	std::string textures;
	std::string textureName;
	std::string textureSpecularMapName;
	std::string textureNormalMapName;
	std::string textureNameExt;

	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;   // Pointer to the image data
	BYTE*             bits;  // Image width and height
	GLfloat           aniso; // Anisotropic Filtering Parameters

	CommonFunctions& CF;
};
}
