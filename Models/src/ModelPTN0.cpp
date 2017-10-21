#include "../../Models/inc/ModelPTN0.h"

// CONSTRUCTOR / DESTRUCTOR
Models::ModelPTN0::ModelPTN0(CommonFunctions* _CF, std::string _modelFolder) :
	                         modelFolder(_modelFolder)
{
	CF = _CF;
	CommonFunctions::getFromDB(modelFolder, "modelName", modelName);

	CommonFunctions::getFromDB(modelFolder, "modelPosition", modelPosition);
	CommonFunctions::getFromDB(modelFolder, "modelScale", modelScale);
	CommonFunctions::getFromDB(modelFolder, "modelRotateAround", modelRotateAround);
	CommonFunctions::getFromDB(modelFolder, "angle", angle);

	// MODEL and TEXTUREs
	modelPTNLoader = new Loader::ModelLoaderLearningOpenGL(CF, const_cast<char *>((modelFolder + modelName + ".3ds").c_str()));
	textureLoader = new Loader::TextureLoader(CF, const_cast<char *>(modelFolder.c_str()), modelPTNLoader->getVectorOfMeshes().size());

	// GET VAO
	VAO = modelPTNLoader->getModelVAO();
	// Vector of Meshes
	vectorOfMeshes.resize(modelPTNLoader->getVectorOfMeshes().size());

	for (unsigned int i = 0; i < modelPTNLoader->getVectorOfMeshes().size(); i++)
	{
		vectorOfMeshes[i].VBO = modelPTNLoader->getVectorOfMeshes()[i].VBO;
		vectorOfMeshes[i].IBO = modelPTNLoader->getVectorOfMeshes()[i].IBO;
		vectorOfMeshes[i].numIndices = modelPTNLoader->getVectorOfMeshes()[i].numIndices;

		vectorOfMeshes[i].texture0ID = textureLoader->getVectorOfMeshes()[i].texture0ID;
	}

	// MODEL VARIABLES
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
}

Models::ModelPTN0::~ModelPTN0()
{
	std::cout << "ModelPTN0 destructor called!" << std::endl;
}
// FUNCTIONs
// GET
GLuint Models::ModelPTN0::getModelVAO()
{
	return VAO;
}

glm::mat4 Models::ModelPTN0::getModelMatrix()
{
	return modelMatrix;
}

glm::vec3 Models::ModelPTN0::getModelPosition()
{
	return modelPosition;
}

glm::vec3 Models::ModelPTN0::getModelScale()
{
	return modelScale;
}

glm::vec3 Models::ModelPTN0::getModelRotation()
{
	return modelRotateAround;
}

GLfloat Models::ModelPTN0::getModelAngle()
{
	return angle;
}

std::vector<Models::Mesh>  Models::ModelPTN0::getVectorOfMeshes()
{
	return vectorOfMeshes;
}
// SET
void Models::ModelPTN0::setModelPosition(glm::vec3 _modelPosition)
{
	modelMatrix = glm::mat4(1.0f);
	modelPosition = _modelPosition;
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
}

void Models::ModelPTN0::setModelScale(glm::vec3 _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);
}

void Models::ModelPTN0::setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle)
{
	modelMatrix = glm::mat4(1.0f);
	angle = _angle;
	modelRotateAround = _modelRotateAround;
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
}
