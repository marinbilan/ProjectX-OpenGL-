#include "../../Models/inc/ModelTerrain0.h"

// CONSTRUCTOR / DESTRUCTOR
Models::ModelTerrain0::ModelTerrain0(CommonFunctions* _CF, std::string _modelFolder, std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders) :
	                         modelFolder(_modelFolder)
{
	CF = _CF;
	//
	// HEIGHTMAP
	//
	//FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; //pointer to the image, once loaded

	//const char* heightMap = "Test";
	//fif = FreeImage_GetFileType(heightMap, 0);
	//if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(heightMap);

	//FIBITMAP *dib(0);                    //pointer to the image data
	//if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, heightMap);

	//BYTE* bits(0);                       //image width and height
	//bits = FreeImage_GetBits(dib);

	//RGBQUAD color;
	//FreeImage_GetPixelColor(dib, 125, 2, &color);

	//std::cout << "ColorR: " << float(color.rgbRed) << std::endl;
	//std::cout << "ColorG: " << float(color.rgbGreen) << std::endl;
	//std::cout << "ColorB: " << float(color.rgbBlue) << std::endl;

	GLfloat SIZE = 800;

	//GLfloat MAX_HEIGHT = 20;
	//GLfloat MAX_PIXEL_COLOR = 255 + 255 + 255;

	// GLuint VERTEX_COUNT = FreeImage_GetHeight(dib);	// GLuint  VERTEX_COUNT = 128;
	GLuint VERTEX_COUNT = 128;

	// float H[256][256];

	//for (int i = 0; i < VERTEX_COUNT; i++) {
	//	for (int j = 0; j < VERTEX_COUNT; j++) {
	//		FreeImage_GetPixelColor(dib, i, j, &color);
	//		float height = (float(color.rgbRed) + float(color.rgbGreen) + float(color.rgbBlue)) / MAX_PIXEL_COLOR;
	//		H[i][j] = MAX_HEIGHT * height;
	//		std::cout << ".. calculating.." << std::endl;
	//	}
	//}

	GLuint count = VERTEX_COUNT * VERTEX_COUNT;
	std::cout << "VERTEX_COUNT: " << VERTEX_COUNT << std::endl;
	// std::cout << H[5][5] << std::endl;

	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* textureCoords;
	GLuint*  indices;

	vertices = new GLfloat[count * 3];
	textureCoords = new GLfloat[count * 2];
	normals = new GLfloat[count * 3];
	indices = new GLuint[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];

	numInd = 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1);

	GLuint vertexPointer = 0;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {

			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0; // H[i][j]; // getHeight(120, 20, &fif, dib); //  40 * sin(0.1*i) + 40 * sin(0.1*j);
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);

			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;

			vertexPointer++;
		}
	}

	GLuint pointer = 0;

	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {

			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	// CREATE VAO 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// CREATE VBOs
	vboID1;
	glGenBuffers(1, &vboID1);
	glBindBuffer(GL_ARRAY_BUFFER, vboID1);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	vboID2;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, 2 * count * sizeof(GLfloat), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	vboID3;
	glGenBuffers(1, &vboID3);
	glBindBuffer(GL_ARRAY_BUFFER, vboID3);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInd*sizeof(GLuint), indices, GL_STATIC_DRAW);

	// MODEL VARIABLES
	modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	angle = 0.0;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);

	backgroundTextureID = loadTexturePNG("_src/_models/terrain/textures/grass.png");
	std::cout << "backgroundTextureID = " << backgroundTextureID << std::endl;

	rTextureID = loadTexturePNG("_src/_models/terrain/textures/dirt.png");
	std::cout << "rTextureID = " << rTextureID << std::endl;

	gTextureID = loadTexturePNG("_src/_models/terrain/textures/sand.png");
	std::cout << "gTextureID = " << gTextureID << std::endl;

	bTextureID = loadTexturePNG("_src/_models/terrain/textures/path.png");
	std::cout << "bTextureID = " << bTextureID << std::endl;

	blendMapID = loadTexturePNG("_src/_models/terrain/textures/blendMap.png");
	std::cout << "blendMapID = " << blendMapID << std::endl;
}

Models::ModelTerrain0::~ModelTerrain0()
{
	std::cout << "ModelTerrain0 destructor called!" << std::endl;
}
// FUNCTIONs
// GET
std::string Models::ModelTerrain0::getModelName()
{
	return modelName;
}

GLuint Models::ModelTerrain0::getModelVAO()
{
	return VAO;
}

glm::mat4 Models::ModelTerrain0::getModelMatrix()
{
	return modelMatrix;
}

glm::vec3 Models::ModelTerrain0::getModelPosition()
{
	return modelPosition;
}

glm::vec3 Models::ModelTerrain0::getModelScale()
{
	return modelScale;
}

glm::vec3 Models::ModelTerrain0::getModelRotation()
{
	return modelRotateAround;
}

GLfloat Models::ModelTerrain0::getModelAngle()
{
	return angle;
}

std::vector<Models::Mesh>  Models::ModelTerrain0::getVectorOfMeshes()
{
	return vectorOfMeshes;
}
// SET
void Models::ModelTerrain0::setModelPosition(glm::vec3 _modelPosition)
{
	modelMatrix = glm::mat4(1.0f);
	modelPosition = _modelPosition;
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
}

void Models::ModelTerrain0::setModelScale(glm::vec3 _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);
}

void Models::ModelTerrain0::setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle)
{
	modelMatrix = glm::mat4(1.0f);
	angle = _angle;
	modelRotateAround = _modelRotateAround;
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
}

// LOAD PNG Texture
GLuint Models::ModelTerrain0::loadTexturePNG(const char* filename) {

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; //pointer to the image, once loaded
	FIBITMAP *dib(0);                    //pointer to the image data
	BYTE* bits(0);                       //image width and height
	unsigned int width(0), height(0);    //OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	// Novo
	RGBQUAD color;
	FreeImage_GetPixelColor(dib, 20, 20, &color);
	std::cout << "Color: " << float(color.rgbGreen) << std::endl;
	int heightImag = FreeImage_GetHeight(dib);
	std::cout << "Image width : " << width << " Image height : " << height << std::endl;
	//

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits); // bits = imageData
																								// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpWidth, bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return success
	return gl_texID;
};