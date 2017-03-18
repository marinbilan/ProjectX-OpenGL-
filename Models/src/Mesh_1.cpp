#include <iostream>
#include <string>

#include "../../Models/inc/Mesh_1.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Mesh_1::Mesh_1(
	GLuint   _num_verts,
	GLfloat* _vertices,
	GLfloat* _normals,
	GLfloat* _textureCoords,
	Shaders::ShadersIf::ShadersIf* _shader,
	Camera::CameraIf::CameraIf* _camera,
	GLfloat* _light)
{
	num_verts = _num_verts;
	vertices = _vertices;
	normals = _normals;
	textureCoords = _textureCoords;

	modelMatrix = glm::mat4(1.0f);
	//
	// ADD SHADER(s)
	//
	shader = _shader;
	camera = _camera;
	//
	// CREATE MODEL
	//
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * num_verts*sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * num_verts * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * num_verts * sizeof(GLfloat), 3 * num_verts * sizeof(GLfloat), normals);
	glBufferSubData(GL_ARRAY_BUFFER, 6 * num_verts * sizeof(GLfloat), 2 * num_verts * sizeof(GLfloat), textureCoords);
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
	glVertexAttribPointer(shader->getNormalsID(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * num_verts * sizeof(GLfloat)));
	glVertexAttribPointer(shader->getTextureCoordsID(), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(6 * num_verts * sizeof(GLfloat)));

	glUseProgram(0);
}

Models::Mesh_1::~Mesh_1()
{
	std::cout << "Mesh_1 destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Mesh_1::VertexAttribPointers()
{
}

void Models::Mesh_1::renderModel()
{
	//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 5.0f));
	//modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));	
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
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
	//camera->updateCameraUniform(shader);
	//glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	//
	// LIGHT CLASS
	//
	//GLfloat lightPosition[] = { 0.0f, 155.0f, 155.0f };
	//glUniform3f(shader->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);

	//GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };
	//glUniform3f(shader->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	//
	// TEXTURE CLASS ATTRIBs
	//
	//GLfloat shineDamper = 10.0f;
	//glUniform1f(shader->getshineDamperID(), shineDamper);

	//GLfloat reflectivity = 1.0f;
	//glUniform1f(shader->getreflectivityID(), reflectivity);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glDrawArrays(GL_TRIANGLES, 0, num_verts);
	//
	// DISABLE EVERYTHING
	//
	glDisableVertexAttribArray(shader->getPositionsID());
	glDisableVertexAttribArray(shader->getNormalsID());
	glDisableVertexAttribArray(shader->getTextureCoordsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


