#ifndef MODELLOADER__
#define MODELLOADER__

#include "../if/LoaderIf.h"
//
// GLM
//
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"

namespace Loader
{
struct Vertex
{
	glm::vec3 position;
	glm::vec2 textureCoord;
	glm::vec3 normal;

	Vertex() {}

	Vertex(glm::vec3& _position, glm::vec2& _textureCoord, glm::vec3& _normal)
	{
		position = _position;
		textureCoord = _textureCoord;
		normal = _normal;
	}
};

class ModelLoader : public LoaderIf::LoaderIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	ModelLoader(char*                          _modelName,
		        char*                          _textureShaderParams,
		        Shaders::ShadersIf::ShadersIf* _shader);

	~ModelLoader();
	//
	// FUNCTIONs
	// 
	virtual GLuint getNumberOfMeshes();

	virtual bool initFromScene(const aiScene* _pScene);
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh);
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, ModelLoader& info)
	{


		return output;
	}

//private:
	struct MeshEntry 
	{
		void init(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices);

		GLuint VBO;
		GLuint IBO;

		GLuint numIndices;

		GLfloat shineDamper;
		GLfloat reflectivity;
	};

	GLuint VAO;	
	GLuint numberOfMeshes;

	glm::mat4 modelMatrix;
	std::vector<MeshEntry> meshesVector;

	char*                          modelPath;
	char*                          textureShaderParams;
	Shaders::ShadersIf::ShadersIf* shader;
};
}

#endif
