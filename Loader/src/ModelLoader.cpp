#include "../../Loader/inc/ModelLoader.h"

// CONSTRUCTORs / DESTRUCTORs
Loader::ModelLoader::ModelLoader(char* _modelName,
	                             char*  _textureShaderParams)
{
	modelMatrix = glm::mat4(1.0f);
	modelPath = _modelName;
	textureShaderParams = _textureShaderParams;
	// CREATE MODEL
	Assimp::Importer Importer;
	std::string model = "model.3ds";

	pScene = Importer.ReadFile(modelPath + model, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene)
	{
		std::cout << "pScene->mNumMeshes: " << pScene->mNumMeshes << std::endl;
		numberOfMeshes = pScene->mNumMeshes;
		bool Ret = initFromScene(pScene);
	}
	else
	{
		std::cout << "Error parsing: " << modelPath << " " << model << " " << Importer.GetErrorString() << std::endl;
	}

	Importer.FreeScene();
}

Loader::ModelLoader::~ModelLoader()
{
	std::cout << "ModelLoader destructor called!" << std::endl;
	// delete pScene;
}
//
// FUNCTION(s) - Add Clean function
// 
bool Loader::ModelLoader::initFromScene(const aiScene* _pScene)
{
	meshesVector.resize(_pScene->mNumMeshes);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//std::ifstream modelParams(textureShaderParams);
	//std::string str;

	for (unsigned int i = 0; i < meshesVector.size(); i++) {
		const aiMesh* paiMesh = _pScene->mMeshes[i];
		initMesh(i, paiMesh);
		// Parse params
		/*
        std::getline(modelParams, str);
		std::istringstream buf(str);
		for (std::string word; buf >> word;)
		{
			if (word == "shineDamper")
			{
				buf >> word;
				meshesVector[i].shineDamper = atof(word.c_str());
				std::cout << meshesVector[i].shineDamper;
			}
			if (word == "reflectivity")
			{
				buf >> word;
				meshesVector[i].reflectivity = atof(word.c_str());
				std::cout << meshesVector[i].reflectivity;
			}
		}
		std::cout << std::endl;
		*/
	}

	return true;
}

void Loader::ModelLoader::initMesh(GLuint _index, const aiMesh* _paiMesh)
{
	std::vector<Vertex>       vertices; // PER MESH
	std::vector<unsigned int> indices;  // PER MESH

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < _paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(_paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(_paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = _paiMesh->HasTextureCoords(0) ? &(_paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
			     glm::vec2(pTexCoord->x, pTexCoord->y),
			     glm::vec3(pNormal->x, pNormal->y, pNormal->z));

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++) {
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}
	meshesVector[_index].init(vertices, indices);
}

void Loader::ModelLoader::MeshEntry::init(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
{
	numIndices = _indices.size();
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &_indices[0], GL_STATIC_DRAW);
}

// GET
GLuint Loader::ModelLoader::getNumberOfMeshes()
{
	return numberOfMeshes;
}
