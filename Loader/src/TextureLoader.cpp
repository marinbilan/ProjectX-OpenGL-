#include "../../Loader/inc/TextureLoader.h"

// CONSTRUCTORs / DESTRUCTORs
Loader::TextureLoader::TextureLoader(CommonFunctions* _CF, char* _texturesFolderPath, GLuint _numberOfTextures)
{
	CF = _CF;

	texturesFolderPath = _texturesFolderPath;
	numberOfTextures = _numberOfTextures; // Should be equal to number od meshes
	// PATH
	textures = "textures/";
	textureName = "texture";
	textureNameExt = ".png";

	// Init vectorOfMeshes
	vectorOfMeshes.resize(_numberOfTextures);
	// Start LOGGing
	CommonFunctions::INFOCMD(LOG "---> TEXTURES from " + std::string(_texturesFolderPath) + " construction start. Number of textures = " + std::to_string(numberOfTextures)) ;
	CF->LOGFILE(LOG"---> TEXTURES from " + std::string(_texturesFolderPath) + " construction start. Number of textures = " + std::to_string(numberOfTextures));
	
	setTextureForEachMesh();
	
	CommonFunctions::INFOCMD(LOG "<--- TEXTURES from " + std::string(_texturesFolderPath) + " construction over.");
	CF->LOGFILE(LOG("<--- TEXTURES from " + std::string(_texturesFolderPath) + " construction over."));
}

Loader::TextureLoader::~TextureLoader()
{
	std::cout << "TextureLoaderX destructor called!" << std::endl;
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
// SET
void Loader::TextureLoader::setTextureForEachMesh()
{
	for (GLuint i = 0; i < numberOfTextures; i++) {
		std::string textureFile = texturesFolderPath + textures + textureName + std::to_string(i) + textureNameExt;

		int texID = createSingleTexture(textureFile);
		CommonFunctions::INFOCMD(LOG "--> Texture " + std::to_string(i) + ": " + textureFile + " created.");
		CF->LOGFILE(LOG "--> Texture " + std::to_string(i) + ": " + textureFile + " created.");

		vectorOfMeshes[i].texture0ID = texID;
	}
}
