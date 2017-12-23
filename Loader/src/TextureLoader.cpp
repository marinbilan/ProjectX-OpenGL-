#include "../../Loader/inc/TextureLoader.h"

// CONSTRUCTORs / DESTRUCTORs
Loader::TextureLoader::TextureLoader(CommonFunctions* _CF, 
	                                 char* _modelFolder,
	                                 GLuint _numberOfTextures) 
	                                 :
	                                 modelFolder(_modelFolder),
	                                 numberOfTextures(_numberOfTextures)
{
	// COMMON FUNCTIONS
	CF = _CF;

	loadTModelPTNTextures();
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
	textureSpecularMapName = "textureSM";
	textureNormalMapName = "textureNM";
	textureNameExt = ".png";

	// Init vectorOfMeshes
	vectorOfMeshes.resize(numberOfTextures);

	CF->LOGFILE(LOG"---> START TEXTURES from " + std::string(modelFolder) + " construction start. Number of textures = " + std::to_string(numberOfTextures) );

	setTextureForEachMesh();

	CF->LOGFILE(LOG("<--- END TEXTURES from " + std::string(modelFolder) + " construction over."));
}

// SET
void Loader::TextureLoader::setTextureForEachMesh()
{
	for (GLuint i = 0; i < numberOfTextures; i++) 
	{
		GLuint textureWidth;
		GLuint textureHeight;
		GLfloat textureSize;
		GLfloat bitsInMB = 8388608; // 1048576 * 8

		std::string textureFile = modelFolder + textures + textureName + std::to_string(i) + textureNameExt;
		int texID = createSingleTexture(textureWidth, textureHeight, textureSize, textureFile);
		CF->LOGFILE(LOG "--> Texture " + std::to_string(i) + ": " + textureFile + " created. Texture ID = " + std::to_string(texID));
		vectorOfMeshes[i].texture0ID = texID;
		vectorOfMeshes[i].textureWidth = textureWidth;
		vectorOfMeshes[i].textureHeight = textureHeight;
		vectorOfMeshes[i].textureSizeMB = textureSize / bitsInMB;

		// CHECK if mesh (texture) has SpecularMap - Fill struct Mesh
		std::string isSpecularMap;
		CF->getStringFromDB(modelFolder, "meshSpecular" + std::to_string(i), isSpecularMap);

		if (std::stoi(isSpecularMap))
		{
			GLuint textureWidth = 0;
			GLuint textureHeight = 0;
			GLfloat textureSize = 0;

			std::string textureSpecularMapFile = modelFolder + textures + textureSpecularMapName + std::to_string(i) + textureNameExt;
			int texSpecularMapID = createSingleTexture(textureWidth, textureHeight, textureSize, textureSpecularMapFile);
			CF->LOGFILE(LOG "--> Specular Map " + std::to_string(i) + ": " + textureSpecularMapFile + " created. Specular Map Texture ID = " + std::to_string(texSpecularMapID));
			vectorOfMeshes[i].textureSpecularMap0ID = texSpecularMapID;
			vectorOfMeshes[i].textureSpecularlMapWidth = textureWidth;
			vectorOfMeshes[i].textureSpecularMapHeight = textureHeight;
			vectorOfMeshes[i].textureSpecularlMapSizeMB = textureSize / bitsInMB;
		}

		// CHECK if mesh (texture) has NormalMap - Fill struct Mesh
		std::string isNormalMap;
		CF->getStringFromDB(modelFolder, "meshTexture" + std::to_string(i), isNormalMap);

		if (std::stoi(isNormalMap))
		{
			GLuint textureWidth = 0;
			GLuint textureHeight = 0;
			GLfloat textureSize = 0;

			std::string textureNormalMapFile = modelFolder + textures + textureNormalMapName + std::to_string(i) + textureNameExt;
			int texNormalMapID = createSingleTexture(textureWidth, textureHeight, textureSize, textureNormalMapFile);
			CF->LOGFILE(LOG "--> Texture Normal Map " + std::to_string(i) + ": " + textureNormalMapFile + " created. Normal Map Texture ID = " + std::to_string(texNormalMapID));
			vectorOfMeshes[i].textureNormalMap0ID = texNormalMapID;
			vectorOfMeshes[i].textureNormalMapWidth = textureWidth;
			vectorOfMeshes[i].textureNormalMapHeight = textureHeight;
			vectorOfMeshes[i].textureNormalMapSizeMB = textureSize / bitsInMB;
		}
	}
}

GLuint Loader::TextureLoader::createSingleTexture(GLuint& _textureWidth, GLuint& _textureHeight, GLfloat& _textureSize, std::string& _textureName)
{
	width = 0;
	height = 0;

	fif = FIF_UNKNOWN;
	dib = 0;
	bits = 0;

	fif = FreeImage_GetFileType(_textureName.c_str(), 0);

	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(_textureName.c_str());
		std::cout << _textureName.c_str() << "FIF UNKNOWN!!!!" << std::endl;
	}
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

	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(_textureName.c_str());
		std::cout << "FIF UNKNOWN!!!!" << std::endl;
	}
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
