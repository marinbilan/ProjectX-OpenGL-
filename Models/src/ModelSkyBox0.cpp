//#include <iostream>
//#include <string>

#include "../../Models/inc/ModelSkyBox0.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::ModelSkyBox0::ModelSkyBox0(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera)
{
	//
	// ADD SHADER(s)
	//
	shader = _shader;
	camera = _camera;

	modelMatrix = glm::mat4(1.0f);
	//
	// CREATE MODEL
	//
	const char* skyBox[] = 
	{ 
		"_src/skyBox/right.png", 
		"_src/skyBox/left.png", 
		"_src/skyBox/top.png", 
		"_src/skyBox/bottom.png", 
		"_src/skyBox/back.png", 
		"_src/skyBox/front.png" 
	};

	num_ver = 36;

	GLfloat SIZE = 500.0f;

	GLfloat verts[] = {
		-SIZE,  SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		-SIZE,  SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		SIZE, -SIZE,  SIZE
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 3 * num_ver * sizeof(GLfloat), verts, GL_STATIC_DRAW); // 3 = x, y, z
	//
	// TEXTUREs
	//
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP*         dib = 0;            //pointer to the image data
	BYTE*             bits = 0;           

	glGenTextures(1, &texID);	
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	unsigned int width = 0;
	unsigned int height = 0;

	for (int i = 0; i < 6; i++)
	{
		fif = FreeImage_GetFileType(skyBox[i], 0);
		dib = FreeImage_Load(fif, skyBox[i]);

		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		FreeImage_FlipVertical(dib);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		FreeImage_Unload(dib);
	}
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	VertexAttribPointers();

	std::cout << "ModelSkyBox0 created! ID = " << texID << std::endl;
}

Models::ModelSkyBox0::~ModelSkyBox0()
{
	std::cout << "ModelSkyBox0 destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::ModelSkyBox0::VertexAttribPointers()
{
	glUseProgram(shader->getShaderProgramID());
	glVertexAttribPointer(shader->getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glUseProgram(0);
}

void Models::ModelSkyBox0::renderModel()
{
	//
	// Bind VAO and Activate SHADER(s)
	//
	glBindVertexArray(VAO);
	glUseProgram(shader->getShaderProgramID());
	//
	// ENABLE ATTRIBs
	//
	glEnableVertexAttribArray(shader->getPositionsID());
	//
	// UPDATE UNIFORMs
	//
	camera->stopTranslate();
	camera->updateCameraUniform(shader);
	camera->updateCameraPosition();
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform3f(shader->getCameraPositionID(), camera->getcameraPosition().x, camera->getcameraPosition().y, camera->getcameraPosition().z);
	GLfloat lightPosition[] = { 0.0f, 5.0f, 15.0f };
	GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };
	glUniform3f(shader->getlightPositionID(), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(shader->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	//
	// ACTIVE TEXTURE
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID); // Bind texture that we want to use to TEXTURE UNIT 0
	//
	// RENDER SKYBOX
	//
	glDrawArrays(GL_TRIANGLES, 0, num_ver);
	//
	// DISABLE TEXTURE
	//
	glDisableVertexAttribArray(shader->getPositionsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


