#ifndef MODEL_6__
#define MODEL_6__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class Model_6 : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_6(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera, GLfloat* _light);

	~Model_6();
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
	friend std::ostream& operator<<(std::ostream& output, Model_6& info)
	{
		return output;
	}
	
private:
	//
	// VAO
	//
	GLuint VAO;

	GLint num_ver;
	GLuint num_ind;

	GLuint VBO;
	GLuint IBO;
	GLuint textureID;
	//
	// SHADER
	//
	Shaders::ShadersIf::ShadersIf* shader;
	//
	// CAMERA
	//
	Camera::CameraIf::CameraIf* camera;
	//
	// MODEL VARIABLE
	
	glm::mat4 modelMatrix;
	//glm::mat4 allRotsMatrix = glm::mat4(1.0f);
	////
	//// LIGHT
	////
	//GLfloat* light;
};
}

#endif
