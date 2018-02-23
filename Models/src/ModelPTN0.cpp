#include "../../Models/inc/ModelPTN0.h"

// CONSTRUCTOR / DESTRUCTOR
Models::ModelPTN0::ModelPTN0(CommonFunctions& _CF, 
	                         std::string _modelFolder, 
	                         std::vector<Shaders::ShadersIf::ShadersIf*>& vectorShaderIf)
	                         :
	                         CF(_CF),
	                         modelFolder(_modelFolder), 
	                         m_vectorShaderIf(vectorShaderIf)
{
	CF.getStringFromDB(modelFolder, "modelName", modelName);
	modelFullName = _modelFolder + modelName;
	CF.LOGFILE(LOG "START constructing " + modelFolder + modelName + " object.");

	CF.getFromDB(modelFolder, "modelPosition", modelPosition);
	CF.getFromDB(modelFolder, "modelScale", modelScale);
	CF.getFromDB(modelFolder, "modelRotateAround", modelRotateAround);
	CF.getFromDB(modelFolder, "angle", angle);

	if (CF.checkError())
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
	Loader::ModelLoaderLearningOpenGL modelPTNLoader(CF, const_cast<char *>((modelFolder).c_str()));
	Loader::TextureLoader             textureLoader(CF, const_cast<char *>(modelFolder.c_str()), modelPTNLoader.getVectorOfMeshes().size());

	// GET VAO
	VAO = modelPTNLoader.getModelVAO();
	vectorOfMeshes.resize(modelPTNLoader.getVectorOfMeshes().size());

	std::string meshTempShaderName;
	for (int i = 0; i < modelPTNLoader.getVectorOfMeshes().size(); i++)
	{
		// VBO
		vectorOfMeshes[i].VBO = modelPTNLoader.getVectorOfMeshes()[i].VBO;
		// IBO
		vectorOfMeshes[i].IBO = modelPTNLoader.getVectorOfMeshes()[i].IBO;
		// numIndices
		vectorOfMeshes[i].numIndices = modelPTNLoader.getVectorOfMeshes()[i].numIndices;
		// Find Shader From DB and shaderVector
		CF.getStringFromDB(modelFolder, "meshShader" + std::to_string(i), meshTempShaderName);
		for (auto& it : m_vectorShaderIf)
		{
			if (!(it)->getShaderName().compare(meshTempShaderName))
			{
				m_vectorShaderIf[i]->getShaderName() = (it)->getShaderName();
				vectorOfMeshes[i].meshVectorShaderIf = it;
			}
		}
		// texture0ID
		vectorOfMeshes[i].texture0ID = textureLoader.getVectorOfMeshes()[i].texture0ID;
		// textureSpecularMap0ID
		vectorOfMeshes[i].textureSpecularMap0ID = textureLoader.getVectorOfMeshes()[i].textureSpecularMap0ID;
		// textureNormalMap0ID
		vectorOfMeshes[i].textureNormalMap0ID = textureLoader.getVectorOfMeshes()[i].textureNormalMap0ID;
	}

	// MODEL VARIABLES
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);

	// some msg here ...
}

// GET
std::string& Models::ModelPTN0::getModelName()
{
	return modelName;
}

GLuint Models::ModelPTN0::getModelVAO()
{
	return VAO;
}

glm::mat4& Models::ModelPTN0::getModelMatrix()
{
	return modelMatrix;
}

glm::vec3& Models::ModelPTN0::getModelPosition()
{
	return modelPosition;
}

glm::vec3& Models::ModelPTN0::getModelScale()
{
	return modelScale;
}

glm::vec3& Models::ModelPTN0::getModelRotation()
{
	return modelRotateAround;
}

GLfloat Models::ModelPTN0::getModelAngle()
{
	return angle;
}

std::vector<Models::Mesh>& Models::ModelPTN0::getVectorOfMeshes()
{
	return vectorOfMeshes;
}
// SET
void Models::ModelPTN0::setModelPosition(glm::vec3& _modelPosition)
{
	//modelMatrix = glm::mat4(1.0f);
	//modelPosition = _modelPosition;
	//modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);


	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), _modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
}

void Models::ModelPTN0::setModelScale(glm::vec3& _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);
}

void Models::ModelPTN0::setModelRotation(glm::vec3& _modelRotateAround, GLfloat _angle)
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