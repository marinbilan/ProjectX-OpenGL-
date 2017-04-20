#ifndef MODELLOADERASSIMPPTN__
#define MODELLOADERASSIMPPTN__
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
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

class ModelLoaderAssimpPTN : public ModelsIf::ModelsIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	ModelLoaderAssimpPTN(char*                          _modelPath,  
		                 Texture::TextureIf::TextureIf* _textureLoader,
		                 char*                          _textureShaderParams,
				         Shaders::ShadersIf::ShadersIf* _shader, 
				         Camera::CameraIf::CameraIf*    _camera,    
				         GLfloat*                       _light);                       

	~ModelLoaderAssimpPTN();
	//
	// FUNCTIONs
	// 
	virtual bool initFromScene(const aiScene* _pScene);
	virtual void initMesh(GLuint _index, const aiMesh* _paiMesh);
	// SETs
	virtual void setModelScale(glm::vec3 _modelScale);
	virtual void setModelRotation(GLfloat _angle, glm::vec3 _modelRotateAround);
	virtual void setModelPosition(glm::vec3 _modelPosition);
	// GET
	virtual GLuint getNumberOfMeshes();

	virtual glm::vec3 getModelScale();
	virtual glm::vec3 getModelRotation();
	virtual glm::vec3 getModelPosition();

	virtual void render();
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, ModelLoaderAssimpPTN& info)
	{
		return output;
	}
	
private:
	struct MeshEntry {

		void init(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices);

		GLuint VBO;
		GLuint IBO;

		GLuint numIndices;
		//
		// MESH SHADER PARAMs
		//
		GLfloat shineDamper;
		GLfloat reflectivity;
	};
	//
	// CONSTRUCTOR params
	//
	char*                          modelPath;
	Texture::TextureIf::TextureIf* textureLoader;
	char*                          textureShaderParams;
	Shaders::ShadersIf::ShadersIf* shader;
	Camera::CameraIf::CameraIf*    camera;	
	GLfloat*                       light;
	//
	// PARAMs
	//
	glm::mat4 modelMatrix;

	glm::vec3 modelPosition;
	GLfloat   angle;
	glm::vec3 modelRotateAround;
	glm::vec3 modelScale;	
	//
	// MODEL VARIABLE	
	//
	GLuint VAO;
	GLuint numberOfMeshes;
	std::vector<MeshEntry> meshesVector;
	std::vector<GLuint>    texturesVectorId;
};
}

#endif
