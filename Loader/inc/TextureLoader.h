#ifndef TEXTURELOADER__
#define TEXTURELOADER__

#include "../if/LoaderIf.h"

namespace Loader
{
class TextureLoader : public LoaderIf::LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	TextureLoader(CommonFunctions* _CF, char* _texturesFolderPath, GLuint _numberOfTextures);
	~TextureLoader();

	// FUNCTIONs
	virtual GLuint createSingleTexture(std::string& _textureName);
	// GET
	std::vector<Loader::Mesh> getVectorOfMeshes();
	// SET
	virtual void setTextureForEachMesh();

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, TextureLoader& info)
	{
		// output << "" << std::endl;
		return output;
	}

private:
	CommonFunctions* CF;

	char* texturesFolderPath;
	GLuint numberOfTextures;

	std::string textures;
	std::string textureName;
	std::string textureNameExt;

	GLuint textureID;

	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;   // Pointer to the image data
	BYTE*             bits;  // Image width and height
	GLfloat           aniso; // Anisotropic Filtering Parameters

	std::vector<Mesh> vectorOfMeshes;
};
}

#endif
