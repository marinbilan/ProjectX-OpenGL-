#include <iostream>
#include <string>

#include "../../Textures/inc/TextureLoaderX.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Texture::TextureLoaderX::TextureLoaderX()
{
}

Texture::TextureLoaderX::~TextureLoaderX()
{
	std::cout << "TextureLoaderX destructor called!" << std::endl;
}
//
// FUNCTIONs
//
// SET
void Texture::TextureLoaderX::loadSingleTexture2DID(char* _textureName)
{
	width = 0;
	height = 0;

	fif = FIF_UNKNOWN;
	dib = 0;
	bits = 0;

	fif = FreeImage_GetFileType(_textureName, 0);

	if (fif == FIF_UNKNOWN)                fif = FreeImage_GetFIFFromFilename(_textureName);
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, _textureName);

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
	aniso = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	FreeImage_Unload(dib);
}

void Texture::TextureLoaderX::loadVectorOfTextures2DID(char* _texturesFolderPath, GLuint _numberOfTextures)
{
	std::cout << "TextureLoaderX constructor called! " << std::endl;
	texturesFolderPath = _texturesFolderPath;
	numberOfTextures = _numberOfTextures;

	for (GLuint i = 0; i < numberOfTextures; i++) {
		std::string textureName = "texture";
		std::string textureNameExt = ".png";
		std::string textureFile = texturesFolderPath + textureName + std::to_string(i) + textureNameExt;

		vectorOfTextures2DID.push_back(createSingleTexture2DID(textureFile));
	}
}

GLuint Texture::TextureLoaderX::getSingleTexture2DID()
{
	return textureID;
}

std::vector<GLuint> Texture::TextureLoaderX::getVectorOfTextures2DID()
{
	return vectorOfTextures2DID;
}
//
// PRIVATE
//
GLuint Texture::TextureLoaderX::createSingleTexture2DID(std::string& _textureName)
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
	aniso = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	FreeImage_Unload(dib);

	return textureID;
}





