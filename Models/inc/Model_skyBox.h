#ifndef MODEL_SKYBOX__
#define MODEL_SKYBOX__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"
//
// ShaderIf
//
#include "../../Shaders/if/ShaderIf.h"

namespace Models
{
class Model_skyBox : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_skyBox(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera);

	~Model_skyBox();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual void VertexAttribPointers();
	virtual void renderModel();
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Model_skyBox& info)
	{
		return output;
	}
	
private:
	//
	// MODEL VARIABLE(s)
	//
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint texID = 0;

	GLuint num_ver;

	glm::mat4 modelMatrix;
	//
	// SHADER(s)
	//
	Shaders::ShadersIf::ShadersIf* shader;
	//
	// CAMERA
	//
	Camera::CameraIf::CameraIf* camera;
};
}

#endif
