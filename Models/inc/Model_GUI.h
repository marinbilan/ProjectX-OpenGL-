#ifndef MODEL_GUI__
#define MODEL_GUI__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

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
	Model_GUI(char* _fileName,
		      Shaders::ShadersIf::ShadersIf* _shader,
		      GLuint _textureID,
		      glm::vec3 _position, 
		      glm::vec3 _scale);

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

	glm::vec3 position;
	glm::vec3 scale;
	//
	// SHADER(s)
	//
	Shaders::ShadersIf::ShadersIf* shader;
	char* fileName;
	GLuint textureID;
};
}

#endif
