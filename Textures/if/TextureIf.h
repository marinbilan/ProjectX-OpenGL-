#ifndef TEXTUREIF__
#define TEXTUREIF__

#include <iostream>
#include <string>
#include <vector>
//
// GLEW
//
#include "../../__libs/glew-1.13.0/include/GL/glew.h"
//
// FreeImage
//
#include "../../__libs/FreeImage/include/FreeImage.h"

namespace Texture
{
namespace TextureIf
{
class TextureIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] TexturesIf() {}
	//
	virtual ~TextureIf()
	{
		std::cout << "TextureIf destructor called!" << std::endl;
	}
	//
	// FUNCTIONs
	//
	// SET
	virtual void loadSingleTexture2DID(char* _textureName) {}
	virtual void loadVectorOfTextures2DID(char* _texturesFolderPath, GLuint _numberOfTextures) {}
	// GET
	virtual GLuint getSingleTexture2DID() { return 0; }
	virtual std::vector<GLuint> getVectorOfTextures2DID() { return dummyReturn; }

private:
	std::vector<GLuint> dummyReturn;
};
}
}

#endif