#include "../../Models/inc/Model_AssimpNormalMap.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_AssimpNormalMap::Model_AssimpNormalMap(const std::string& _filename,
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

	const aiScene* pScene = Importer.ReadFile(_filename.c_str() + model, 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals | 
		aiProcess_FlipUVs | 
		aiProcess_CalcTangentSpace);

	if (pScene) 
	{
		std::cout << "pScene->mNumMeshes: " << pScene->mNumMeshes << std::endl;

		Ret = InitFromScene(pScene, _filename);
	}
	else 
	{
		printf("Error parsing '%s': '%s'\n", _filename.c_str() + model, Importer.GetErrorString());
	}
}

Models::Model_AssimpNormalMap::~Model_AssimpNormalMap()
{
	std::cout << "Model_AssimpNormalMap destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
//
// MeshEntry inside class Mesh
//
void Models::Model_AssimpNormalMap::MeshEntry::Init(const std::vector<VertexNM>& Vertices, const std::vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();

	GLuint VAO_;

	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNM) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}
//
// Mesh Functions
//
void Models::Model_AssimpNormalMap::Clear()
{
	//for (unsigned int i = 0; i < m_Textures.size(); i++) {
	//	SAFE_DELETE(m_Textures[i]);
	//}
}

bool Models::Model_AssimpNormalMap::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	//m_Textures.resize(pScene->mNumMaterials); CHANGED
	m_Textures.resize(pScene->mNumMeshes + 1);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, Filename);
}

void Models::Model_AssimpNormalMap::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<VertexNM> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent = &(paiMesh->mTangents[i]); // ADDED

		VertexNM v(glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z),
			glm::vec3(pTangent->x, pTangent->y, pTangent->z));

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

bool Models::Model_AssimpNormalMap::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	bool Ret = true;

	for (unsigned int i = 0; i < pScene->mNumMeshes; i++) {

		m_Textures[i] = NULL;

		std::string textString1 = "texture";
		std::string textString2 = ".png";

		std::string textureFile = Filename + textString1 + std::to_string(i) + textString2;
		std::cout << "textureFile: " << textureFile << std::endl;

		m_Textures[i] = new TextureNM(GL_TEXTURE_2D, textureFile);
		Ret = m_Textures[i]->Load();
	}

	m_Textures[1] = new TextureNM(GL_TEXTURE_2D, Filename + "texture1.png");
	Ret = m_Textures[1]->Load();

	return Ret;
}

void Models::Model_AssimpNormalMap::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	for (unsigned int i = 0; i < m_Entries.size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNM), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexNM), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNM), (const GLvoid*)20);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNM), (const GLvoid*)32); // tangent

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

		// m_Textures[i]->Bind(GL_TEXTURE0); // TO DO also for NORMALMAP

		//glUniform1i(shader->getmodelTextureID(), 5); // order texture
		//glUniform1i(shader->getnormalMapID(), 6);    // normal map

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, 5);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, 6);

		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}






