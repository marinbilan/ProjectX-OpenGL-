#pragma once
#include "../if/ModelIf.h"

namespace Models
{
class ModelPTN0 : public ModelsIf::ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelPTN0(CommonFunctions* _CF, 
		      std::string _modelFolder, 
		      std::vector<std::shared_ptr<Shaders::ShadersIf::ShadersIf>> _vectorOfShaders);
	~ModelPTN0();

	// FUNCTIONs
	void                      initPTNModel();
	// GET
	std::string               getModelName();
	GLuint                    getModelVAO();
	std::vector<Models::Mesh> getVectorOfMeshes();
	glm::mat4                 getModelMatrix();
	glm::vec3                 getModelPosition();
	glm::vec3                 getModelScale();
	glm::vec3                 getModelRotation();
	GLfloat                   getModelAngle();
	// SET
	void                      setModelPosition(glm::vec3 _modelPosition);
	void                      setModelScale(glm::vec3 _modelScale);
	void                      setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle);
	// Add setModelAngle

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ModelPTN0& info)
	{
		output << " " << std::endl;
		output << "[ MODEL ]" << std::endl;
		output << " Model Name:  " << info.modelFullName << std::endl;
		output << " Model VAO              = " << info.VAO << std::endl;
		output << " Model Number of Meshes = " << info.vectorOfMeshes.size() << std::endl;
		output << " Model Meshes Size      = " << info.modelMeshSizeMB << "[MB]" << std::endl;
		output << " Model Textures Size    = " << info.modelTextureSizeMB << "[MB]" << std::endl;
		output << " Model TOTAL SIZE       = " << info.modelTotalSizeMB << "[MB]" << std::endl;

		output << "   [ MESHEs ]" << std::endl;

		std::vector<Models::Mesh>::iterator it;
		for (it = info.vectorOfMeshes.begin(); it != info.vectorOfMeshes.end(); ++it)
		{
			output << *it << std::endl;
		}

		return output;
	}
private:
	// CONSTRUCTOR params
	CommonFunctions* CF;
	std::vector<std::shared_ptr<Shaders::ShadersIf::ShadersIf>> vectorOfShaders;

	std::string               modelFolder;
	std::string               modelName;
	std::string               modelFullName;
	GLfloat                   modelMeshSizeMB;
	GLfloat                   modelTextureSizeMB;
	GLfloat                   modelTotalSizeMB;

	GLuint                    VAO;
	std::vector<Models::Mesh> vectorOfMeshes;

	glm::mat4                 modelMatrix;
	glm::vec3                 modelPosition;
	glm::vec3                 modelScale;
	glm::vec3                 modelRotateAround;
	GLfloat                   angle;
};
}
