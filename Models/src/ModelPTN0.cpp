#include "../../Models/inc/ModelPTN0.h"

// CONSTRUCTOR / DESTRUCTOR
Models::ModelPTN0::ModelPTN0(CommonFunctions* _CF, std::string _modelFolder, std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders) :
	                         modelFolder(_modelFolder)
{
	CF = _CF;
	CommonFunctions::getFromDB(modelFolder, "modelName", modelName);
	modelFullName = _modelFolder + modelName;

	CommonFunctions::getFromDB(modelFolder, "modelPosition", modelPosition);
	CommonFunctions::getFromDB(modelFolder, "modelScale", modelScale);
	CommonFunctions::getFromDB(modelFolder, "modelRotateAround", modelRotateAround);
	CommonFunctions::getFromDB(modelFolder, "angle", angle);

	// MODEL and TEXTUREs
	modelPTNLoader = new Loader::ModelLoaderLearningOpenGL(CF, const_cast<char *>((modelFolder + modelName + ".3ds").c_str()));
	modelPTNLoader->loadModelPTN();
	textureLoader = new Loader::TextureLoader(CF, const_cast<char *>(modelFolder.c_str()), modelPTNLoader->getVectorOfMeshes().size());
	textureLoader->loadTModelPTNTextures();

	// GET VAO
	VAO = modelPTNLoader->getModelVAO();
	// Vector of Meshes
	vectorOfMeshes.resize(modelPTNLoader->getVectorOfMeshes().size());

	modelMeshSizeMB = 0;
	modelTextureSizeMB = 0;
	std::vector<Shaders::ShadersIf::ShadersIf*>::iterator it;
	std::string meshTempShaderName;
	for (unsigned int i = 0; i < modelPTNLoader->getVectorOfMeshes().size(); i++)
	{
		// MODEL LOADER
		vectorOfMeshes[i].VBO = modelPTNLoader->getVectorOfMeshes()[i].VBO;
		vectorOfMeshes[i].IBO = modelPTNLoader->getVectorOfMeshes()[i].IBO;
		vectorOfMeshes[i].numIndices = modelPTNLoader->getVectorOfMeshes()[i].numIndices;
		vectorOfMeshes[i].meshSizeMB = modelPTNLoader->getVectorOfMeshes()[i].meshSizeMB;
		modelMeshSizeMB += vectorOfMeshes[i].meshSizeMB;
		// ----== GIVE ME SHADERS FOR EACH MESH ==----
		// Get shader name from DataBase.txt, find shader in _vectorOfShaders and set shader pointer in mesh 
		CommonFunctions::getFromDB(modelFolder, "meshShader" + std::to_string(i), meshTempShaderName);
		for (it = _vectorOfShaders.begin(); it != _vectorOfShaders.end(); it++)
		{
			if (!(*it)->getShaderName().compare(meshTempShaderName))
			{
				std::cout << "FOUND MESH SHADER NAME: " << meshTempShaderName << std::endl;
				vectorOfMeshes[i].meshShaderName = (*it)->getShaderName();
				vectorOfMeshes[i].meshShaderPtr = *it;
				// Add mesh shader name
				vectorOfMeshes[i].meshShaderName = (*it)->getShaderName();
			}
		}
		// ----====----
		// TEXTURE LOADER
		vectorOfMeshes[i].texture0ID = textureLoader->getVectorOfMeshes()[i].texture0ID;
		vectorOfMeshes[i].textureWidth = textureLoader->getVectorOfMeshes()[i].textureWidth;
		vectorOfMeshes[i].textureHeight = textureLoader->getVectorOfMeshes()[i].textureHeight;
		vectorOfMeshes[i].textureSizeMB = textureLoader->getVectorOfMeshes()[i].textureSizeMB;

		modelTextureSizeMB += vectorOfMeshes[i].textureSizeMB;
	}
	modelTotalSizeMB = modelMeshSizeMB + modelTextureSizeMB;

	// MODEL VARIABLES
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);

	std::cout << "ModelPTN " << modelFullName << " created!" << std::endl;
}

Models::ModelPTN0::~ModelPTN0()
{
	std::cout << "ModelPTN0 destructor called!" << std::endl;
}
// FUNCTIONs
// GET
std::string Models::ModelPTN0::getModelName()
{
	return modelName;
}

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
	//modelMatrix = glm::mat4(1.0f);
	//modelPosition = _modelPosition;
	//modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);


	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), _modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
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
// OPERATORs
void Models::ModelPTN0::printINFO()
{
	std::cout << *this;
}