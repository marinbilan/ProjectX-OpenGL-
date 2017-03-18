#ifndef MODEL_AssimpNormalMap__
#define MODEL_AssimpNormalMap__
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
struct VertexNM
{
	glm::vec3 pos;
	glm::vec2 tex;
	glm::vec3 normal;
	glm::vec3 tangent;

	VertexNM() {}

	VertexNM(const glm::vec3& _pos, const glm::vec2& _tex, const glm::vec3& _normal, const glm::vec3& _tangent)
	{
		pos = _pos;
		tex = _tex;
		normal = _normal;
		tangent = _tangent;
	}
};

class TextureNM
{
public:
	TextureNM(GLenum _textureTarget, const std::string& _fileName) {

		textureTarget = _textureTarget;
		fileName = _fileName;
	}

	bool Load() {
		std::cout << "_fileName: " << fileName << std::endl;

		unsigned int width = 0;
		unsigned int height = 0;

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP*         dib = 0;            //pointer to the image data
		BYTE*             bits = 0;           //image width and height

		fif = FreeImage_GetFileType(fileName.c_str(), 0);

		if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(fileName.c_str());
		if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, fileName.c_str());

		bits = FreeImage_GetBits(dib);

		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		FreeImage_FlipVertical(dib);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		FreeImage_Unload(dib);

		return true;
	}

	void Bind(GLenum TextureUnit) {

		glActiveTexture(TextureUnit); // textureTarget GL_TEXTURE0
		glBindTexture(textureTarget, textureID); // textureTarget GL_TEXTURE_2D
		std::cout << TextureUnit << "..." << textureID << std::endl;
	}

private:
	std::string fileName;

	GLenum textureTarget;
	GLuint textureID;
};

class Model_AssimpNormalMap : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_AssimpNormalMap(const std::string& _filename,           // MODEL FILE NAME
				 Shaders::ShadersIf::ShadersIf* _shader, // SHADER
				 Camera::CameraIf::CameraIf* _camera,    // CAMERA
				 GLfloat* _light);                       // LIGHT

	~Model_AssimpNormalMap();
	//
	//
	// FUNCTIONs
	// 
	//
	//
	// ASSIMP
	//
	virtual void Clear();

	virtual bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	virtual void InitMesh(unsigned int Index, const aiMesh* paiMesh);
	virtual bool InitMaterials(const aiScene* pScene, const std::string& Filename);

	virtual void Render();
	//
	//
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Model_AssimpNormalMap& info)
	{
		return output;
	}
	
private:

	struct MeshEntry {

		void Init(const std::vector<VertexNM>& Vertices, const std::vector<unsigned int>& Indices);

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};
	//
	// MODEL VARIABLE	
	//
	glm::mat4 modelMatrix;

	std::vector<MeshEntry> m_Entries;
	std::vector<TextureNM*>  m_Textures;
	//
	// SHADER
	//
	Shaders::ShadersIf::ShadersIf* shader;
	//
	// CAMERA
	//
	Camera::CameraIf::CameraIf* camera;
	//
	// LIGHT
	//
	//GLfloat* light;
};
}

#endif
