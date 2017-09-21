#ifndef MODELLOADER__
#define MODELLOADER__

#include "../if/LoaderIf.h"

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
		position     = _position;
		textureCoord = _textureCoord;
		normal       = _normal;
	}
};

class ModelLoader : public LoaderIf::LoaderIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelLoader(char* _modelName,
		        char*  _textureShaderParams);
	~ModelLoader();
	// FUNCTIONs
	virtual GLuint getNumberOfMeshes();

	virtual bool initFromScene(const aiScene* _pScene);
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh);
	// OPERATORs
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
	};

	GLuint VAO;	
	GLuint numberOfMeshes;

	glm::mat4 modelMatrix;
	std::vector<MeshEntry> meshesVector;

	const aiScene* pScene;

	char* modelPath;
	char* textureShaderParams;
};
}

#endif
