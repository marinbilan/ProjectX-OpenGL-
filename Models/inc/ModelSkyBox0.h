#pragma once
#include "../if/ModelIf.h"

namespace Models
{
class ModelSkyBox0 : public ModelsIf::ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ModelSkyBox0(std::vector<Shaders::ShadersIf::ShadersIf*>& vectorShaders,
		         Camera::CameraIf::CameraIf* _camera);

	~ModelSkyBox0();

	// FUNCTIONs
	GLuint                         getModelVAO();
	GLuint                         getModelVBO();
	Shaders::ShadersIf::ShadersIf& getShader();
	glm::mat4                      getModelMatrix();
	GLuint                         getTextureID();
	GLuint                         getNumVertices();

	// TODO: Remove
	virtual void VertexAttribPointers();
	virtual void renderModel();

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ModelSkyBox0& info)
	{
		return output;
	}
	
private:
	GLuint VAO;
	GLuint VBO;
	GLuint texID;
	GLuint num_ver;

	glm::mat4 modelMatrix;
	Shaders::ShadersIf::ShadersIf* shader;
	Camera::CameraIf::CameraIf* camera;
};
}
