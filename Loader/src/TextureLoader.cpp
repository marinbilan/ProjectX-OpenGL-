#include "../../Loader/inc/TextureLoader.h"

// CONSTRUCTORs / DESTRUCTORs
Loader::TextureLoader::TextureLoader(CommonFunctions* _CF, char* _texturesFolderPath, GLuint _numberOfTextures) :
	texturesFolderPath(_texturesFolderPath), numberOfTextures(_numberOfTextures)
{
	// COMMON FUNCTIONS
	CF = _CF;
}

Loader::TextureLoader::~TextureLoader()
{
	std::cout << "TextureLoaderX destructor called!" << std::endl;
}

void Loader::TextureLoader::loadTModelPTNTextures()
{
    // PATH
	textures = "textures/";
	textureName = "texture";
	textureNameExt = ".png";

	// Init vectorOfMeshes
	vectorOfMeshes.resize(numberOfTextures);
	// Start LOGGing
	// CommonFunctions::INFOCMD(LOG "---> TEXTURES from " + std::string(texturesFolderPath) + " construction start. Number of textures = " + std::to_string(numberOfTextures));
	CF->LOGFILE(LOG"---> TEXTURES from " + std::string(texturesFolderPath) + " construction start. Number of textures = " + std::to_string(numberOfTextures) );

	setTextureForEachMesh();

	// CommonFunctions::INFOCMD(LOG "<--- TEXTURES from " + std::string(texturesFolderPath) + " construction over.");
	CF->LOGFILE(LOG("<--- TEXTURES from " + std::string(texturesFolderPath) + " construction over."));
}
GLuint Loader::TextureLoader::createSingleTexture(GLuint& _textureWidth, GLuint& _textureHeight, GLfloat& _textureSize, std::string& _textureName)
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
	_textureWidth = width;
	_textureHeight = height;
	_textureSize = FreeImage_GetMemorySize(dib);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	FreeImage_FlipVertical(dib);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);

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
// GET
std::vector<Loader::Mesh> Loader::TextureLoader::getVectorOfMeshes()
{
	return vectorOfMeshes;
}

GLuint Loader::TextureLoader::createSingleTexture(std::string& _textureName)
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
	glGenerateMipmap(GL_TEXTURE_2D);

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

// SET
void Loader::TextureLoader::setTextureForEachMesh()
{
	for (GLuint i = 0; i < numberOfTextures; i++) {
		std::string textureFile = texturesFolderPath + textures + textureName + std::to_string(i) + textureNameExt;

		GLuint textureWidth;
		GLuint textureHeight;
		GLfloat textureSize;
		GLfloat bitsInMB = 8388608; // 1048576 * 8

		int texID = createSingleTexture(textureWidth, textureHeight, textureSize, textureFile);

		// CommonFunctions::INFOCMD(LOG "--> Texture " + std::to_string(i) + ": " + textureFile + " created.");
		CF->LOGFILE(LOG "--> Texture " + std::to_string(i) + ": " + textureFile + " created.");

		vectorOfMeshes[i].texture0ID = texID;
		vectorOfMeshes[i].textureWidth = textureWidth;
		vectorOfMeshes[i].textureHeight = textureHeight;
		vectorOfMeshes[i].textureSizeMB = textureSize / bitsInMB;
	}
}
