#ifndef MODELLEARNOPENGL0__
#define MODELLEARNOPENGL0__
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class ModelLearnOpenGL0 : public ModelsIf::ModelsIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	ModelLearnOpenGL0(Loader::ModelLoader*           _modelPTNLoader,
		             Loader::TextureLoader*         _textureLoader,
		             char*                          _textureShaderParams,
		             Shaders::ShadersIf::ShadersIf* _shader);                       
	~ModelLearnOpenGL0();
	//
	// FUNCTIONs
	// 
	// SET TODO
	virtual void setModelScale(glm::vec3 _modelScale);
	virtual void setModelRotation(GLfloat _angle, glm::vec3 _modelRotateAround);
	virtual void setModelPosition(glm::vec3 _modelPosition);
	// GET
	virtual glm::vec3& getModelScale();
	virtual glm::vec3& getModelRotation();
	virtual glm::vec3& getModelPosition();

	virtual void render();
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, ModelLearnOpenGL0& info)
	{
		return output;
	}
	
private:
	//
	// CONSTRUCTOR params
	//
	Loader::ModelLoader*           modelPTNLoader;
	Loader::TextureLoader*         textureLoader;
	char*                          textureShaderParams;
	Shaders::ShadersIf::ShadersIf* shader;
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
	std::vector<GLuint> texturesVectorId;
};
}

#endif
