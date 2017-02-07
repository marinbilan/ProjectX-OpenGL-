#include <iostream>
#include <string>

#include "../../Models/inc/Model_GUI.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_GUI::Model_GUI(Shaders::ShadersIf::ShadersIf* _shader)
{
	//
	// ADD SHADER(s)
	//
	shader = _shader;

	modelMatrix = glm::mat4(1.0f);
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

	fif = FreeImage_GetFileType("socuwan.png", 0);

	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename("socuwan.png");
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, "socuwan.png");

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

	FreeImage_Unload(dib);
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	VertexAttribPointers();
}

Models::Model_GUI::~Model_GUI()
{
	std::cout << "Model_GUI destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Model_GUI::VertexAttribPointers()
{
	glUseProgram(shader->getShaderProgramID());
	glVertexAttribPointer(shader->getPositionsID(), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glUseProgram(0);
}

void Models::Model_GUI::renderModel()
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
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f, 0.5f, 0.f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));

	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Disable OK
	glDisable(GL_DEPTH_TEST); // Stop testing depths

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID); // Bind texture that we want to use to TEXTURE UNIT 0
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


