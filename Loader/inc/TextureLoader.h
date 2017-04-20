#ifndef TEXTURELOADER__
#define TEXTURELOADER__

#include "../if/LoaderIf.h"

namespace Loader
{
class TextureLoader : public LoaderIf::LoaderIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	TextureLoader(char* _textureFolderPath, GLuint _numberOfTextures);

	~TextureLoader();
	//
	// FUNCTIONs
	// 
	// TEXTUREs
	virtual GLuint loadTexture2DID(std::string& _textureName);
	virtual std::vector<GLuint> loadtexture2DVectorIDs(char* _textureFolderPath, GLuint _numberOfTextures);
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, TextureLoader& info)
	{
		output << "" << std::endl;
		output << "numberOfTextures: " << info.numberOfTextures << std::endl;
		output << "" << std::endl;

		return output;
	}

private:
	//
	// Constructor Parameters
	// 
	char*  textureFolderPath;
	GLuint numberOfTextures;

	GLuint textureID;
	std::vector<GLuint> textureIDs;
	//
	// FreeImage Parameters
	//
	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;            // pointer to the image data
	BYTE*             bits;           // image width and height
	//
	// Anisotropic Filtering Parameters
	//
	GLfloat aniso;
};
}

#endif
