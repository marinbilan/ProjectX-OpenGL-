#ifndef MODELGUI0__
#define MODELGUI0__

//#include <iostream>
//#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class ModelGUI0 : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ModelGUI0(char* _fileName,
		      Shaders::ShadersIf::ShadersIf* _shader,
		      GLuint _textureID,
		      glm::vec3 _position, 
		      glm::vec3 _scale);

	~ModelGUI0();
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
	friend std::ostream& operator<<(std::ostream& output, ModelGUI0& info)
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
