#ifndef MODELPTN0__
#define MODELPTN0__

#include "../if/ModelIf.h"

namespace Models
{
class ModelPTN0 : public ModelsIf::ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelPTN0(CommonFunctions* _CF, std::string _modelFolder, std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders);
	~ModelPTN0();
	// FUNCTIONs
	// GET
	void initPTNModel();

	std::string getModelName();
	virtual GLuint getModelVAO();
	std::vector<Models::Mesh> getVectorOfMeshes();

	virtual glm::mat4 getModelMatrix();
	virtual glm::vec3 getModelPosition();
	virtual glm::vec3 getModelScale();
	virtual glm::vec3 getModelRotation();
	virtual GLfloat   getModelAngle();
	// SET
	virtual void setModelPosition(glm::vec3 _modelPosition);
	virtual void setModelScale(glm::vec3 _modelScale);
	virtual void setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle);
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
	std::vector<Shaders::ShadersIf::ShadersIf*> vectorOfShaders;

	std::string                        modelFolder;
	std::string                        modelName;
	std::string                        modelFullName;
	GLfloat                            modelMeshSizeMB;
	GLfloat                            modelTextureSizeMB;
	GLfloat                            modelTotalSizeMB;

	Loader::ModelLoaderLearningOpenGL* modelPTNLoader;
	Loader::TextureLoader*             textureLoader;

	GLuint                             VAO;
	std::vector<Models::Mesh>          vectorOfMeshes;

	glm::mat4                          modelMatrix;
	glm::vec3                          modelPosition;
	glm::vec3                          modelScale;
	glm::vec3                          modelRotateAround;
	GLfloat                            angle;
};
}
#endif
