#include "../../Models/inc/ModelSkyBox0.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// CONSTRUCTORs / DESTRUCTOR(s)
Models::ModelSkyBox0::ModelSkyBox0(std::vector<Shaders::ShadersIf::ShadersIf*>& vectorShaders)
{
	for (auto& it : vectorShaders)
	{
		if (!(it)->getShaderName().compare("ShaderSkyBox0"))
		{
			shader = it;
		}
	}

	modelMatrix = glm::mat4(1.0f);

	// CREATE MODEL
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

	// TEXTUREs
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

	std::cout << "ModelSkyBox0 created! ID = " << texID << std::endl;
}

Models::ModelSkyBox0::~ModelSkyBox0()
{
	std::cout << "ModelSkyBox0 destructor called!" << std::endl;
}

// FUNCTIONs
GLuint Models::ModelSkyBox0::getModelVAO()
{
	return VAO;
}

GLuint Models::ModelSkyBox0::getModelVBO()
{
	return VBO;
}


Shaders::ShadersIf::ShadersIf& Models::ModelSkyBox0::getShader()
{
	return *shader;
}

glm::mat4& Models::ModelSkyBox0::getModelMatrix()
{
	return modelMatrix;
}

GLuint Models::ModelSkyBox0::getTextureID()
{
	return texID;
}

GLuint Models::ModelSkyBox0::getNumVertices()
{
	return num_ver;
}