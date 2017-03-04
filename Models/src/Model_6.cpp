#include <iostream>
#include <string>

#include "../../Models/inc/Model_6.h"
//
// DATABASE [DB]
//
#include "../../Db/ModelsDb/_cubeuv2.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_6::Model_6(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera, GLfloat* _light)
{
	modelMatrix = glm::mat4(1.0f);
	//
	// ADD SHADER(s)
	//
	shader = _shader;
	camera = _camera;
	//light = _light;	
	//
	// CREATE MODEL
	//
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * cube_num_ver_2*sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * cube_num_ver_2 * sizeof(GLfloat), cube_vert_2);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * cube_num_ver_2 * sizeof(GLfloat), 3 * cube_num_ver_2 * sizeof(GLfloat), cube_normals_2);
	glBufferSubData(GL_ARRAY_BUFFER, 6 * cube_num_ver_2 * sizeof(GLfloat), 2 * cube_num_ver_2 * sizeof(GLfloat), cube_textures_2);
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

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FreeImage_Unload(dib);
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	glUseProgram(shader->getShaderProgramID());

	glVertexAttribPointer(shader->getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(shader->getNormalsID(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * cube_num_ver_2 * sizeof(GLfloat)));
	glVertexAttribPointer(shader->getTextureCoordsID(), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(6 * cube_num_ver_2 * sizeof(GLfloat)));

	glUseProgram(0);
}

Models::Model_6::~Model_6()
{
	std::cout << "Model_6 destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Model_6::VertexAttribPointers()
{
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	//glUseProgram(shader->getShaderProgramID());
	//glVertexAttribPointer(shader->getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(shader->getTextureCoordsID(), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	////glVertexAttribPointer(shader->getNormalsID(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vert)));
	//glUseProgram(0);
}

void Models::Model_6::renderModel()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 5.0f, 5.0f));
	modelMatrix = glm::rotate(modelMatrix, 1.3f, glm::vec3(1.0f, 1.0f, 1.0f));	
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
	// UPDATE UNIFORMs
	//
	camera->updateCameraUniform(shader);
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	//
	// LIGHT CLASS
	//
	GLfloat lightPosition[] = { 0.0f, 15.0f, 15.0f };
	glUniform3f(shader->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);

	GLfloat lightColour[] = { 1.0f, 1.0f, 0.0f };
	glUniform3f(shader->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	//
	// TEXTURE CLASS ATTRIBs
	//
	GLfloat shineDamper = 10.0f;
	glUniform1f(shader->getshineDamperID(), shineDamper);

	GLfloat reflectivity = 1.0f;
	glUniform1f(shader->getreflectivityID(), reflectivity);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glDrawArrays(GL_TRIANGLES, 0, cube_num_ver_2);

	//
	// Draw second cube
	//
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 13.0f, 13.0f));
	modelMatrix = glm::rotate(modelMatrix, 1.3f, glm::vec3(1.0f, 1.0f, 1.0f));

	//camera->updateCameraUniform(shader);
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, cube_num_ver_2);
	//
	// DISABLE EVERYTHING
	//
	glDisableVertexAttribArray(shader->getPositionsID());
	glDisableVertexAttribArray(shader->getNormalsID());
	glDisableVertexAttribArray(shader->getTextureCoordsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


