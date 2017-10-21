#ifndef MODELSKYBOX0__
#define MODELSKYBOX0__

//#include <iostream>
//#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class ModelSkyBox0 : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ModelSkyBox0(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera);

	~ModelSkyBox0();
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
	friend std::ostream& operator<<(std::ostream& output, ModelSkyBox0& info)
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
