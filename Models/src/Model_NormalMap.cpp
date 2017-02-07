#include <iostream>
#include <string>

#include "../../Models/inc/Model_NormalMap.h"
//
// DATABASE [DB]
//
//#include "../../Db/_dragon.h"
#include "../../Db/_cubeuv.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_NormalMap::Model_NormalMap(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera, GLfloat* _light)
{
	//
	// ADD SHADER(s)
	//
	shader = _shader;
	camera = _camera;
	light = _light;
	//
	// CREATE MODEL
	//
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * cube_num_ver*sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * cube_num_ver * sizeof(GLfloat), cube_vert2);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * cube_num_ver * sizeof(GLfloat), 3 * cube_num_ver * sizeof(GLfloat), cube_normals);
	glBufferSubData(GL_ARRAY_BUFFER, 6 * cube_num_ver * sizeof(GLfloat), 2 * cube_num_ver * sizeof(GLfloat), cube_textures);
	//
	// TEXTURE
	//
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP*         dib = 0;            //pointer to the image data
	BYTE*             bits = 0;           //image width and height

	unsigned int width = 0;
	unsigned int height = 0;

	fif = FreeImage_GetFileType("cubeuvLayout.png", 0);

	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename("cubeuvLayout.png");
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, "cubeuvLayout.png");

	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	glGenTextures(1, &texBufferID);
	glBindTexture(GL_TEXTURE_2D, texBufferID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

	FreeImage_Unload(dib);
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	VertexAttribPointers();
}

Models::Model_NormalMap::~Model_NormalMap()
{
	std::cout << "Model_1 destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Model_NormalMap::VertexAttribPointers()
{
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	glUseProgram(shader->getShaderProgramID());
	
	glVertexAttribPointer(shader->getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(shader->getNormalsID(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * cube_num_ver * sizeof(GLfloat)));
	glVertexAttribPointer(shader->getTextureCoordsID(), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(6 * cube_num_ver * sizeof(GLfloat)));
	glUseProgram(0);
}

void Models::Model_NormalMap::renderModel()
{
	//
	// ... UPDATE MODEL STATE
	//	
	modelMatrix = glm::rotate(glm::mat4(1.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	allRotsMatrix = glm::rotate(glm::mat4(1.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//
	// Bind VAO and Activate SHADER(s)
	//
	glBindVertexArray(VAO);
	glUseProgram(shader->getShaderProgramID());
	//
	// Enable attributes in shaderProgramID
	//
	glEnableVertexAttribArray(shader->getPositionsID());
	glEnableVertexAttribArray(shader->getNormalsID());
	glEnableVertexAttribArray(shader->getTextureCoordsID());
	//
	// ... Update Uniforms ... 
	//     mP		  - shader [ Only once in shader ]
	//     mV		  - camera
	//     mM		  - modelMatrix
	//     mRotations - allRotsMatrix 
	//     vLight     - light
	//
	camera->updateCameraUniform(shader);
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(shader->getNormalsRotationsID(), 1, GL_FALSE, &allRotsMatrix[0][0]);
	glUniform4fv(shader->getLightID(), 1, light);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBufferID);
	//
	// ... DRAW MODEL (MESH) ...
	//
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glDrawElements(GL_TRIANGLES, num_ind, GL_UNSIGNED_INT, NULL);
	glDrawArrays(GL_TRIANGLES, 0, cube_num_ver);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//
	// DISABLE EVERYTHING
	//
	glDisableVertexAttribArray(shader->getPositionsID());
	glDisableVertexAttribArray(shader->getNormalsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


