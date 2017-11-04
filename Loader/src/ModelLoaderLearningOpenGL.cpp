#include "../../Loader/inc/ModelLoaderLearningOpenGL.h"

// CONSTRUCTORs / DESTRUCTORs
Loader::ModelLoaderLearningOpenGL::ModelLoaderLearningOpenGL(CommonFunctions* _CF, 
	                                                         char* _modelFolder) 
	                                                         :
	                                                         modelFolder(_modelFolder)
{
	// Common Functions
	CF = _CF;
    // Get Model Name from DataBase
	CommonFunctions::getFromDB(modelFolder, "modelName", modelName);
	modelName += ".3ds";
}

Loader::ModelLoaderLearningOpenGL::~ModelLoaderLearningOpenGL()
{
	std::cout << "ModelLoader destructor called!" << std::endl;
}

void Loader::ModelLoaderLearningOpenGL::loadModelPTN()
{
	// CREATE MODEL
	Assimp::Importer Importer;
	pScene = Importer.ReadFile((modelFolder + modelName), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	CF->LOGFILE(LOG("---> START " + modelFolder + modelName + " MESHes LOADING. " + "Number of MESHEs = " + std::to_string(pScene->mNumMeshes)));

	if (pScene)
	{
		initScene(pScene);
	}
	else
	{
		CommonFunctions::INFOCMD(LOG "ERROR parsing: " + modelFolder + modelName + ". " + Importer.GetErrorString());
	}

	CF->LOGFILE(LOG("<--- END " + modelFolder + modelName + " MESHes LOADING."));
}

void Loader::ModelLoaderLearningOpenGL::initScene(const aiScene* _pScene)
{
	vectorOfMeshes.resize(_pScene->mNumMeshes);

	// CREATE MODEL
	// Create VAO for whole Model
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	CF->LOGFILE(LOG "--> Model " + modelName + " VAO = " + std::to_string(VAO) + " generated.");

	// START CREATING MESHes
	// Create VBO and IBO for each Mesh in Model
	for (unsigned int i = 0; i < vectorOfMeshes.size(); i++) {
		const aiMesh* paiMesh = _pScene->mMeshes[i];
		// Check if mesh (texture) has NormalMap - Fill struct Mesh
		std::string isNormalMap;
		CommonFunctions::getFromDB(modelFolder, "meshTexture" + std::to_string(i), isNormalMap);
		
		if (std::stoi(isNormalMap))
		{
    		initNormalMapMesh(i, paiMesh);
		}
		else
		{
		    initMesh(i, paiMesh);
		}
	}
}
// MESH
void Loader::ModelLoaderLearningOpenGL::initMesh(GLuint _index, const aiMesh* _paiMesh)
{
	std::vector<Vert>         vertices; // PER MESH [position (x, y, z), texture(u, v), noraml(x, y, z)]
	std::vector<unsigned int> indices;  // PER MESH

	glm::vec3* positionCoord = new glm::vec3(0.0f);
	glm::vec3* textureCoord  = new glm::vec3(0.0f);
	glm::vec3* normalCoord   = new glm::vec3(0.0f);

	for (unsigned int i = 0; i < _paiMesh->mNumVertices; i++) {
		// Positions
		positionCoord->x = _paiMesh->mVertices[i].x;
		positionCoord->y = _paiMesh->mVertices[i].y;
		positionCoord->z = _paiMesh->mVertices[i].z;
		// Texture
		textureCoord->x = _paiMesh->mTextureCoords[0][i].x;
		textureCoord->y = _paiMesh->mTextureCoords[0][i].y;
		// Normals
		normalCoord->x = _paiMesh->mNormals[i].x;
		normalCoord->y = _paiMesh->mNormals[i].y;
		normalCoord->z = _paiMesh->mNormals[i].z;

		Vert v(glm::vec3(positionCoord->x, positionCoord->y, positionCoord->z), // in vec3 position
			   glm::vec2(textureCoord->x, textureCoord->y),                     // in vec2 textureCoordinates
			   glm::vec3(normalCoord->x, normalCoord->y, normalCoord->z));      // in vec3 normal

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++) {
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	// For each Mesh in Model - Create  VBO and IBO
	glGenBuffers(1, &vectorOfMeshes[_index].VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vectorOfMeshes[_index].VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // sizeof(Vert) = 32

	CF->LOGFILE(LOG "--> Model " + modelName + " VBO = " + std::to_string(vectorOfMeshes[_index].VBO) + " generated.");

	glGenBuffers(1, &vectorOfMeshes[_index].IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vectorOfMeshes[_index].IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	CF->LOGFILE(LOG "--> Model " + modelName + " IBO = " + std::to_string(vectorOfMeshes[_index].IBO) + " generated.");

	vectorOfMeshes[_index].numIndices = indices.size(); // For each mesh! Important for rendering!

	//Calculate size for each Mesh
	GLfloat bitsInMB = 8388608; // 1048576 * 8
	//                                   <------------ verts + textureCoords + normals ------------------------------ indices ---------------------------->
	vectorOfMeshes[_index].meshSizeMB = ( _paiMesh->mNumVertices*(3*sizeof(GLuint)+2*sizeof(GLuint)+3*sizeof(GLuint))+_paiMesh->mNumVertices*sizeof(GLuint)) / bitsInMB;

}
// NORMALMAP MESH
void Loader::ModelLoaderLearningOpenGL::initNormalMapMesh(GLuint _index, const aiMesh* _paiMesh)
{
	std::vector<VertNormalMap> vertices; // PER MESH [position (x, y, z), texture(u, v), noraml(x, y, z) tengent(x, y, z)]
	std::vector<unsigned int>  indices;  // PER MESH

	glm::vec3* positionCoord = new glm::vec3(0.0f);
	glm::vec2* textureCoord = new glm::vec2(0.0f);
	glm::vec3* normalCoord = new glm::vec3(0.0f);
	glm::vec3* tangentCoord = new glm::vec3(0.0f);

	for (unsigned int i = 0; i < _paiMesh->mNumVertices; i++) {
		// Positions
		positionCoord->x = _paiMesh->mVertices[i].x;
		positionCoord->y = _paiMesh->mVertices[i].y;
		positionCoord->z = _paiMesh->mVertices[i].z;
		// Texture
		textureCoord->x = _paiMesh->mTextureCoords[0][i].x;
		textureCoord->y = _paiMesh->mTextureCoords[0][i].y;
		// Normals
		normalCoord->x = _paiMesh->mNormals[i].x;
		normalCoord->y = _paiMesh->mNormals[i].y;
		normalCoord->z = _paiMesh->mNormals[i].z;
		// Tangents
		tangentCoord->x = _paiMesh->mTangents[i].x;
		tangentCoord->y = _paiMesh->mTangents[i].y;
		tangentCoord->z = _paiMesh->mTangents[i].z;

		VertNormalMap v(glm::vec3(positionCoord->x, positionCoord->y, positionCoord->z), // in vec3 position
			glm::vec2(textureCoord->x, textureCoord->y),                                 // in vec2 textureCoordinates
			glm::vec3(normalCoord->x, normalCoord->y, normalCoord->z),
			glm::vec3(tangentCoord->x, tangentCoord->y, tangentCoord->z));               // in vec3 normal

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++) {
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	// For each Mesh in Model - Create  VBO and IBO
	glGenBuffers(1, &vectorOfMeshes[_index].VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vectorOfMeshes[_index].VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertNormalMap) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // sizeof(VertNormalMap) = 44

	CF->LOGFILE(LOG "--> Model " + modelName + " VBO = " + std::to_string(vectorOfMeshes[_index].VBO) + " created.");

	glGenBuffers(1, &vectorOfMeshes[_index].IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vectorOfMeshes[_index].IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	CF->LOGFILE(LOG "--> Model " + modelName + " IBO = " + std::to_string(vectorOfMeshes[_index].IBO) + " created.");

	vectorOfMeshes[_index].numIndices = indices.size(); // For each mesh! Important for rendering!

	//Calculate size for each Mesh
	GLfloat bitsInMB = 8388608; // 1048576 * 8
								//                                   <------------ verts + textureCoords + normals ------------------------------ indices ---------------------------->
	vectorOfMeshes[_index].meshSizeMB = (_paiMesh->mNumVertices*(3 * sizeof(GLuint) + 2 * sizeof(GLuint) + 3 * sizeof(GLuint)) + _paiMesh->mNumVertices*sizeof(GLuint)) / bitsInMB;
}

// GET
GLuint Loader::ModelLoaderLearningOpenGL::getModelVAO()
{
	return VAO;
}

std::vector<Loader::Mesh> Loader::ModelLoaderLearningOpenGL::getVectorOfMeshes()
{
	return vectorOfMeshes;
}
