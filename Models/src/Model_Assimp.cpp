#include "../../Models/inc/Model_Assimp.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_Assimp::Model_Assimp(const std::string& _filename,
								   Shaders::ShadersIf::ShadersIf* _shader, 
								   Camera::CameraIf::CameraIf* _camera, 
								   GLfloat* _light)
{
	modelMatrix = glm::mat4(1.0f);
	//
	// ADD SHADER(s)
	//
	const std::string model = "model.3ds";

	shader = _shader;
	camera = _camera;
	//light = _light;	
	//
	// CREATE MODEL
	//
	// Release the previously loaded mesh (if it exists) (Need implementation)
	Clear();

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(_filename.c_str() + model, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) 
	{
		std::cout << "pScene->mNumMeshes: " << pScene->mNumMeshes << std::endl;
		std::cout << "pScene->mNumMaterials: " << pScene->mNumMaterials << std::endl;
		std::cout << "pScene->mNumTextures: " << pScene->mNumTextures << std::endl;

		Ret = InitFromScene(pScene, _filename);
	}
	else 
	{
		printf("Error parsing '%s': '%s'\n", _filename.c_str() + model, Importer.GetErrorString());
	}
}

Models::Model_Assimp::~Model_Assimp()
{
	std::cout << "Model_Assimp destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
//
// MeshEntry inside class Mesh
//
void Models::Model_Assimp::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();

	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}
//
// Mesh Functions
//
void Models::Model_Assimp::Clear()
{
	//for (unsigned int i = 0; i < m_Textures.size(); i++) {
	//	SAFE_DELETE(m_Textures[i]);
	//}
}

bool Models::Model_Assimp::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	//m_Textures.resize(pScene->mNumMaterials); CHANGED
	m_Textures.resize(pScene->mNumMeshes);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, Filename);
}

void Models::Model_Assimp::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	m_Entries[Index].Init(Vertices, Indices);
}

bool Models::Model_Assimp::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	bool Ret = true;

	for (unsigned int i = 0; i < pScene->mNumMeshes; i++) {

		m_Textures[i] = NULL;

		std::string textString1 = "texture";
		std::string textString2 = ".png";

		std::string textureFile = Filename + textString1 + std::to_string(i) + textString2;
		std::cout << "textureFile: " << textureFile << std::endl;

		m_Textures[i] = new Texture(GL_TEXTURE_2D, textureFile);
		Ret = m_Textures[i]->Load();
	}

	return Ret;
}

void Models::Model_Assimp::Render()
{
	glBindVertexArray(VAO_);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_Entries.size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);
		m_Textures[i]->Bind(GL_TEXTURE + i);
		//glUniform1i(shader->getmodelTextureID(), i);    // texture connect with GL_TEXTURE0, GL_TEXTURE1...
		//glActiveTexture(GL_TEXTURE0 + i);
		//glBindTexture(GL_TEXTURE_2D, m_Textures[i]->textureID);

		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glUseProgram(0);
	glBindVertexArray(0);
}






