#pragma once
#include "../if/LoaderIf.h"

namespace Loader
{
struct Vert 
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	Vert(glm::vec3& _position, glm::vec2& _textureCoord, glm::vec3& _normal)
	{
		Position  = _position;
		TexCoords = _textureCoord;
		Normal    = _normal;
	}

private:
glm::vec3 Position;
glm::vec2 TexCoords;
glm::vec3 Normal;
};

struct VertNormalMap
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	VertNormalMap(glm::vec3& _position, glm::vec2& _textureCoord, glm::vec3& _normal, glm::vec3& _tangent)
	{
		Position = _position;
		TexCoords = _textureCoord;
		Normal = _normal;
		Tangent = _tangent;
	}

private:
glm::vec3 Position;
glm::vec2 TexCoords;
glm::vec3 Normal;
glm::vec3 Tangent;
};

class ModelLoaderLearningOpenGL : public LoaderIf::LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelLoaderLearningOpenGL(CommonFunctions& _CF, char* _modelFolder);
	~ModelLoaderLearningOpenGL();

	// FUNCTIONs
	void loadModelPTN();
	void initScene(const aiScene* _pScene);
	void initMesh(GLuint _index, const aiMesh* _paiMesh);
	void initNormalMapMesh(GLuint _index, const aiMesh* _paiMesh);
	// GET
	GLuint                     getModelVAO();
	std::vector<Loader::Mesh>& getVectorOfMeshes();

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ModelLoaderLearningOpenGL& info)
	{
		return output;
	}
private:
	GLuint            VAO;	

	std::string       modelFolder;
	std::string       modelName;

	std::vector<Mesh> vectorOfMeshes;

	const aiScene*    pScene;
	CommonFunctions& CF;
};
}
