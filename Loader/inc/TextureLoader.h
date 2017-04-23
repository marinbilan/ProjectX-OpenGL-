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
	TextureLoader();
	~TextureLoader();
	//
	// FUNCTIONs
	// 
	virtual void loadSingleTexture2DID(char* _textureName);
	virtual void loadVectorOfTextures2DID(char* _texturesFolderPath, GLuint _numberOfTextures);

	virtual GLuint getSingleTexture2DID();
	virtual std::vector<GLuint> getVectorOfTextures2DID();
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
	char*  texturesFolderPath;
	GLuint numberOfTextures;

	GLuint textureID;
	std::vector<GLuint> vectorOfTextures2DID;

	// FreeImage Parameters
	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;            // pointer to the image data
	BYTE*             bits;           // image width and height
									  // Anisotropic Filtering Parameters
	GLfloat aniso;
	//
	// PRIVATE FUNCTIONs
	//
	virtual GLuint createSingleTexture2DID(std::string& _textureName);
};
}

#endif
