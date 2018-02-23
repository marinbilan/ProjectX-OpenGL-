#ifndef MODELTERRAIN0__
#define MODELTERRAIN0__

#include "../if/ModelIf.h"

namespace Models
{
class ModelTerrain0 : public ModelsIf::ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelTerrain0(CommonFunctions* _CF, std::string _modelFolder, std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders);
	~ModelTerrain0();
	// FUNCTIONs
	// GET
	std::string&               getModelName();
	GLuint             getModelVAO();
	std::vector<Models::Mesh>& getVectorOfMeshes();

	glm::mat4& getModelMatrix();
	glm::vec3& getModelPosition();
	glm::vec3& getModelScale();
	glm::vec3& getModelRotation();
	GLfloat    getModelAngle();
	// SET
	void setModelPosition(glm::vec3 _modelPosition);
	void setModelScale(glm::vec3 _modelScale);
	void setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle);
	GLuint Models::ModelTerrain0::loadTexturePNG(const char* filename);
	// Add setModelAngle

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ModelTerrain0& info)
	{
		output << " " << std::endl;
		output << "----==== MODEL ====---- " << std::endl;
		output << "Model Name:  " << info.modelFolder << std::endl;
		output << " Model Number of Meshes : " << info.vectorOfMeshes.size() << std::endl;
		output << " Model VAO              : " << info.VAO << std::endl;

		output << " ----==== MESHEs ====---- " << std::endl;
		std::vector<Models::Mesh>::iterator it;
		for (it = info.vectorOfMeshes.begin(); it != info.vectorOfMeshes.end(); ++it)
		{
			output << *it << std::endl;
		}
		output << "----========------ " << std::endl;
		return output;
	}
	// TEXTUREs ID
	GLuint backgroundTextureID;
	GLuint rTextureID;
	GLuint gTextureID;
	GLuint bTextureID;
	GLuint blendMapID;
	GLuint vboID1;
	GLuint vboID2;
	GLuint vboID3;
	GLuint indexBufferID;
	GLuint numInd;

private:
	// CONSTRUCTOR params
	CommonFunctions* CF;

	std::string                        modelFolder;
	std::string                        modelName;

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
