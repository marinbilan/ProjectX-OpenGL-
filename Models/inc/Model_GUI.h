#ifndef MODEL_GUI__
#define MODEL_GUI__

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
class Model_GUI : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_GUI(Shaders::ShadersIf::ShadersIf* shader);

	~Model_GUI();
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
	friend std::ostream& operator<<(std::ostream& output, Model_GUI& info)
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
};
}

#endif
