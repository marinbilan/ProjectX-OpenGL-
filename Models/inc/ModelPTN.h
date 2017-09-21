#ifndef MODELPTN__
#define MODELPTN__

#include "../if/ModelIf.h"

namespace Models
{
class ModelPTN : public ModelsIf::ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelPTN(std::string                    _modelPath,
        	 std::string                    _modelName,
		     Loader::ModelLoader*           _modelPTNLoader,
		     Loader::TextureLoader*         _textureLoader,
		     Shaders::ShadersIf::ShadersIf* _shader,
		     glm::vec3                      _modelPosition,
		     glm::vec3                      _modelScale,
		     glm::vec3                      _modelRotateAround,
		     GLfloat                        _angle);
	~ModelPTN();
	// FUNCTIONs
	// SET
	virtual void setModelPosition(glm::vec3 _modelPosition);
	virtual void setModelScale(glm::vec3 _modelScale);
	virtual void setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle);
	// GET
	virtual glm::vec3 getModelPosition();
	virtual glm::vec3 getModelScale();
	virtual glm::vec3 getModelRotation();
	virtual GLuint    getModelAngle();
	// RENDER
	virtual void render();
	virtual void renderDepth(Shaders::ShadersIf::ShadersIf* _shader);
	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ModelPTN& info)
	{
		return output;
	}
private:
	// CONSTRUCTOR params
	std::string                    modelPath;
	std::string                    modelName;
	Loader::ModelLoader*           modelPTNLoader;
	Loader::TextureLoader*         textureLoader;
	Shaders::ShadersIf::ShadersIf* shader;
	glm::vec3                      modelPosition;
	glm::vec3                      modelScale;
	glm::vec3                      modelRotateAround;
	GLfloat                        angle;

	glm::mat4                      modelMatrix;
	// TEXTUREs
	std::vector<GLuint>            texturesVectorId;
};
}
#endif
