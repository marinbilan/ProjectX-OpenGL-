#include <iostream>
#include <string>

#include "../../Models/inc/Model_Water_Tile.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_Water_Tile::Model_Water_Tile(char* _fileName,
	                                       Shaders::ShadersIf::ShadersIf* _shader, 
	                                       Camera::CameraIf::CameraIf* _camera,
	                                       GLuint _textureID,
	                                       glm::vec3 _position, 
	                                       glm::vec3 _scale)
{
	//
	// ADD SHADER(s)
	//
	fileName = _fileName;
	shader = _shader;
	camera = _camera;
	textureID = _textureID;

	position = _position;
	scale = _scale;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = glm::rotate(modelMatrix, -1.55f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
	//
	// CREATE MODEL
	//
	num_ver = 4;
	GLfloat verts[] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 2 * num_ver * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	//
	// TEXTURE
	//
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP*         dib = 0;            //pointer to the image data
	BYTE*             bits = 0;           //image width and height

	unsigned int width = 0;
	unsigned int height = 0;

	fif = FreeImage_GetFileType(fileName, 0);

	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(fileName);
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, fileName);

	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	FreeImage_FlipVertical(dib);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);
	// Za mali kut terena
	float aniso = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	FreeImage_Unload(dib);

	// NORMAL MAP
	fif = FIF_UNKNOWN;
	dib = 0;            //pointer to the image data
	bits = 0;           //image width and height

	width = 0;
	height = 0;

	fif = FreeImage_GetFileType("_src/water/matchingNormalMap.png", 0);

	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename("_src/water/matchingNormalMap.png");
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, "_src/water/matchingNormalMap.png");

	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	glGenTextures(1, &normalMapID);
	glBindTexture(GL_TEXTURE_2D, normalMapID);
	FreeImage_FlipVertical(dib);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

	FreeImage_Unload(dib);
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	VertexAttribPointers();
}

Models::Model_Water_Tile::~Model_Water_Tile()
{
	std::cout << "Model_Water_Tile destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Model_Water_Tile::VertexAttribPointers()
{
	glUseProgram(shader->getShaderProgramID());
	glVertexAttribPointer(shader->getPositionsID(), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glUseProgram(0);
}

void Models::Model_Water_Tile::renderModel()
{
	//
	// Bind VAO and Activate SHADER(s)
	//
	glBindVertexArray(VAO);
	glUseProgram(shader->getShaderProgramID());
	//
	// Enable attributes in shaderProgramID
	//
	glEnableVertexAttribArray(shader->getPositionsID());
	//
	// ... UPDATE UNIFORM(s)
	//	
	camera->updateCameraUniform(shader);
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = glm::rotate(modelMatrix, -1.55f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Disable OK
	glDisable(GL_DEPTH_TEST); // Stop testing depths

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texID); // Bind texture that we want to use to TEXTURE UNIT 0 !REMOVE HARCODED NO 8!
	glUniform1i(shader->getreflectionTextureID(), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 8);	
	glUniform1i(shader->getrefractionTextureID(), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 12);
	glUniform1i(shader->getdudvMapID(), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texID);
	// NORMAL MAP
	glUniform1i(shader->getnormalMapID(), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalMapID);
	//
	// RENDER MODEL (mesh0)
	//
	glDrawArrays(GL_TRIANGLE_STRIP, 0, num_ver);

	// Enable OK
	glEnable(GL_DEPTH_TEST); // Start testing depths
	
	// DISABLE
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(shader->getPositionsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


