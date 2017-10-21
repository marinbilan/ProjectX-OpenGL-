#ifndef MODELLOADERLEARNINGOPENGL__
#define MODELLOADERLEARNINGOPENGL__

#include "../if/LoaderIf.h"

namespace Loader
{
struct Vert 
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
	//glm::vec3 Tangent;   // TODO
	//glm::vec3 Bitangent; // TODO

	// CONSTRUCTORs / DESTRUCTORs
	Vert(glm::vec3& _position, glm::vec2& _textureCoord, glm::vec3& _normal)
	{
		Position  = _position;
		TexCoords = _textureCoord;
		Normal    = _normal;
	}
};

class ModelLoaderLearningOpenGL : public LoaderIf::LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelLoaderLearningOpenGL(CommonFunctions* _CF, char* _modelName);

	~ModelLoaderLearningOpenGL();
	// FUNCTIONs
	void initScene(const aiScene* _pScene);
	void initMesh(GLuint _index, const aiMesh* _paiMesh);
	// GET
	GLuint getModelVAO();
	std::vector<Loader::Mesh> getVectorOfMeshes();

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ModelLoaderLearningOpenGL& info)
	{
		return output;
	}
private:
	CommonFunctions* CF;

	std::string modelName;
	GLuint VAO;	

	const aiScene* pScene;

	std::vector<Mesh> vectorOfMeshes;
};
}
#endif
