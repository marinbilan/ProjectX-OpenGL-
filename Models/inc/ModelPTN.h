#ifndef MODELPTN__
#define MODELPTN__
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class ModelPTN : public ModelsIf::ModelsIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	ModelPTN(char*                          _modelPath,
		     Loader::ModelLoader* _modelPTNLoader,
		     Texture::TextureIf::TextureIf* _textureLoader,
		     char*                          _textureShaderParams,
		     Shaders::ShadersIf::ShadersIf* _shader, 
		     Camera::CameraIf::CameraIf*    _camera,    
		     GLfloat*                       _light);                       

	~ModelPTN();
	//
	// FUNCTIONs
	// 
	// SET
	virtual void setModelScale(glm::vec3 _modelScale);
	virtual void setModelRotation(GLfloat _angle, glm::vec3 _modelRotateAround);
	virtual void setModelPosition(glm::vec3 _modelPosition);
	// GET
	virtual glm::vec3 getModelScale();
	virtual glm::vec3 getModelRotation();
	virtual glm::vec3 getModelPosition();

	virtual void render();
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, ModelPTN& info)
	{
		return output;
	}
	
private:
	//
	// CONSTRUCTOR params
	//
	char*                          modelPath;
	Loader::ModelLoader*           modelPTNLoader;
	Texture::TextureIf::TextureIf* textureLoader;
	char*                          textureShaderParams;
	Shaders::ShadersIf::ShadersIf* shader;
	Camera::CameraIf::CameraIf*    camera;	
	GLfloat*                       light;
	//
	// MODEL params
	//
	glm::mat4 modelMatrix;

	glm::vec3 modelPosition;
	GLfloat   angle;
	glm::vec3 modelRotateAround;
	glm::vec3 modelScale;	
	//
	// TEXTUREs
	//
	std::vector<GLuint>    texturesVectorId;
};
}

#endif
