#include <iostream>
#include <string>

#include "../../Loader/inc/TextureLoader.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Loader::TextureLoader::TextureLoader(char* _textureFolderPath, GLuint _numberOfTextures)
{
	std::cout << "TextureLoader constructor called! " << std::endl;
	textureFolderPath = _textureFolderPath;
	numberOfTextures  = _numberOfTextures;

	textureID = 0;

	width = 0;
	height = 0;
	fif = FIF_UNKNOWN;
	dib = 0;
	bits = 0;

	aniso = 4.0f;

	for (GLuint i = 0; i < numberOfTextures; i++) {

		std::string textureName = "texture";
		std::string textureNameExt = ".png";
		std::string textureFile = textureFolderPath + textureName + std::to_string(i) + textureNameExt;

		textureIDs.push_back(loadTexture2DID(textureFile));
	}
}

Loader::TextureLoader::~TextureLoader()
{
	std::cout << "TextureLoader destructor called!" << std::endl;
}
//
// FUNCTIONs
//
GLuint Loader::TextureLoader::loadTexture2DID(std::string& _textureName)
{
	width = 0;
	height = 0;

	fif = FIF_UNKNOWN;
	dib = 0;           
	bits = 0;          

	fif = FreeImage_GetFileType(_textureName.c_str(), 0);

	if (fif == FIF_UNKNOWN)                fif = FreeImage_GetFIFFromFilename(_textureName.c_str());
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, _textureName.c_str());

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	FreeImage_FlipVertical(dib);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Anisotropic Filtering
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	FreeImage_Unload(dib);

	return textureID;
}
//
// GET
//
std::vector<GLuint> Loader::TextureLoader::loadtexture2DVectorIDs(char* _textureFolderPath, GLuint _numberOfTextures)
{
	textureFolderPath = _textureFolderPath;
	numberOfTextures  = _numberOfTextures;

	textureID = 0;

	width = 0;
	height = 0;
	fif = FIF_UNKNOWN;
	dib = 0;
	bits = 0;

	aniso = 4.0f;

	for (GLuint i = 0; i < numberOfTextures; i++) {

		std::string textureName = "texture";
		std::string textureNameExt = ".png";
		std::string textureFile = textureFolderPath + textureName + std::to_string(i) + textureNameExt;

		textureIDs.push_back(loadTexture2DID(textureFile));
	}

	return textureIDs;
}




