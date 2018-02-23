#include "../../Models/inc/ModelPTN0.h"

// CONSTRUCTOR / DESTRUCTOR
Models::ModelPTN0::ModelPTN0(CommonFunctions* _CF, 
	                         std::string _modelFolder, 
	                         std::vector<std::shared_ptr<Shaders::ShadersIf::ShadersIf>> _vectorOfShaders)
	                         :
	                         CF(_CF),
	                         modelFolder(_modelFolder), 
	                         vectorOfShaders(_vectorOfShaders)
{
	CF->getStringFromDB(modelFolder, "modelName", modelName);
	modelFullName = _modelFolder + modelName;
	CF->LOGFILE(LOG "START constructing " + modelFolder + modelName + " object.");

	CF->getFromDB(modelFolder, "modelPosition", modelPosition);
	CF->getFromDB(modelFolder, "modelScale", modelScale);
	CF->getFromDB(modelFolder, "modelRotateAround", modelRotateAround);
	CF->getFromDB(modelFolder, "angle", angle);

	if (CF->checkError())
	{
		// ERROR INFO
	}
	else
	{
    	initPTNModel();
	}
}

Models::ModelPTN0::~ModelPTN0()
{
	std::cout << "ModelPTN0 destructor called!" << std::endl;
}
// FUNCTIONs
void Models::ModelPTN0::initPTNModel()
{
	// CREATE MODEL and TEXTUREs
	std::unique_ptr<Loader::ModelLoaderLearningOpenGL> modelPTNLoader(new Loader::ModelLoaderLearningOpenGL(*CF, const_cast<char *>((modelFolder).c_str())));
	std::unique_ptr<Loader::TextureLoader> textureLoader(new Loader::TextureLoader(*CF, const_cast<char *>(modelFolder.c_str()), modelPTNLoader->getVectorOfMeshes().size()));

	// GET VAO
	VAO = modelPTNLoader->getModelVAO();
	// Vector of Model Meshes
	vectorOfMeshes.resize(modelPTNLoader->getVectorOfMeshes().size());

	modelMeshSizeMB = 0;
	modelTextureSizeMB = 0;
	std::string meshTempShaderName;
	// FILL DATA for each MESH
	for (int i = 0; i < modelPTNLoader->getVectorOfMeshes().size(); i++)
	{
		// MESH PARAMs from ModelLoaderLearningOpenGL
		vectorOfMeshes[i].VBO = modelPTNLoader->getVectorOfMeshes()[i].VBO;
		vectorOfMeshes[i].IBO = modelPTNLoader->getVectorOfMeshes()[i].IBO;
		vectorOfMeshes[i].numIndices = modelPTNLoader->getVectorOfMeshes()[i].numIndices;
		//vectorOfMeshes[i].meshSizeMB = modelPTNLoader->getVectorOfMeshes()[i].meshSizeMB;
		//modelMeshSizeMB += vectorOfMeshes[i].meshSizeMB;
		// SHADER for each MESH from constructor param _vectorOfShaders
		CF->getStringFromDB(modelFolder, "meshShader" + std::to_string(i), meshTempShaderName);
		for (auto& it : vectorOfShaders)
		{
			if (!(it)->getShaderName().compare(meshTempShaderName))
			{
				vectorOfMeshes[i].meshShaderName = (it)->getShaderName();
				vectorOfMeshes[i].meshShaderPtr = it;
			}
		}
		// TEXTUREs from TextureLoader
		vectorOfMeshes[i].texture0ID = textureLoader->getVectorOfMeshes()[i].texture0ID;
		//vectorOfMeshes[i].textureWidth = textureLoader->getVectorOfMeshes()[i].textureWidth;
		//vectorOfMeshes[i].textureHeight = textureLoader->getVectorOfMeshes()[i].textureHeight;
		//vectorOfMeshes[i].textureSizeMB = textureLoader->getVectorOfMeshes()[i].textureSizeMB;
		//modelTextureSizeMB += vectorOfMeshes[i].textureSizeMB;

		// SPECULAR MAP TEXTUREs LOADER
		vectorOfMeshes[i].textureSpecularMap0ID = textureLoader->getVectorOfMeshes()[i].textureSpecularMap0ID;

		// NORMAL MAP TEXTUREs LOADER
		vectorOfMeshes[i].textureNormalMap0ID = textureLoader->getVectorOfMeshes()[i].textureNormalMap0ID;
	}
	modelTotalSizeMB = modelMeshSizeMB + modelTextureSizeMB;

	// MODEL VARIABLES
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);

	// std::cout << "ModelPTN " << modelFullName << " created!" << std::endl;
}

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