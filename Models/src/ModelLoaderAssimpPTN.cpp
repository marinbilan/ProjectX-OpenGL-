#include "../../Models/inc/ModelLoaderAssimpPTN.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::ModelLoaderAssimpPTN::ModelLoaderAssimpPTN(char*                          _modelPath,
	                                               Texture::TextureIf::TextureIf* _textureLoader,
	                                               char*                          _textureShaderParams,
								                   Shaders::ShadersIf::ShadersIf* _shader, 
								                   Camera::CameraIf::CameraIf*    _camera, 
								                   GLfloat*                       _light)
{
	// CONSTURCOTR params
	modelPath = _modelPath;
	textureLoader = _textureLoader;
	textureShaderParams = _textureShaderParams;
	shader = _shader;
	camera = _camera;
	light = _light;	
	// MODEL params
	modelMatrix = glm::mat4(1.0f);

	modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = -1.55f;
	modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
	//
	// CREATE MODEL
	//
	bool Ret = false;
	Assimp::Importer Importer;
	const std::string model = "model.3ds";

	const aiScene* pScene = Importer.ReadFile(modelPath + model, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) 
	{
		std::cout << "pScene->mNumMeshes: " << pScene->mNumMeshes << std::endl;
		numberOfMeshes = pScene->mNumMeshes;
		//
		// Get textureIDs (GLuint) vector - IMPORTANT: USE ONLY IN RENDER LOOP foreach mesh
		//
		texturesVectorId = textureLoader->getVectorOfTextures2DID();

		Ret = initFromScene(pScene);
	}
	else 
	{
		std::cout << "Error parsing: " << modelPath << " " << model << " " << Importer.GetErrorString() << std::endl;
	}	
}

Models::ModelLoaderAssimpPTN::~ModelLoaderAssimpPTN()
{
	std::cout << "ModelLoaderAssimpPNT destructor called!" << std::endl;
}
//
// FUNCTION(s) - Add Clean function
// 
bool Models::ModelLoaderAssimpPTN::initFromScene(const aiScene* _pScene)
{
	//
	// Meshes - private variable
	//
	meshesVector.resize(_pScene->mNumMeshes);

	glGenVertexArrays(1, &VAO); // Create only one VAO for MODEL and multiple VBO, IBO for each mesh
	glBindVertexArray(VAO);

	std::ifstream modelParams(textureShaderParams);
	std::string str;

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < meshesVector.size(); i++) {
		const aiMesh* paiMesh = _pScene->mMeshes[i];
		// Read each line from modelParams File
		std::getline(modelParams, str);
		// INIT EACH MESH
		initMesh(i, paiMesh);
		// Read params for each mesh in meshVector
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
	}

	return true;
}

void Models::ModelLoaderAssimpPTN::initMesh(GLuint _index, const aiMesh* _paiMesh)
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
// IMPORTANT: init meshes VBOs is local function int MeshEntry (see namespace ..MeshEntry::init...)
void Models::ModelLoaderAssimpPTN::MeshEntry::init(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
{
	numIndices = _indices.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &_indices[0], GL_STATIC_DRAW);
}
// SET
void Models::ModelLoaderAssimpPTN::setModelScale(glm::vec3 _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelLoaderAssimpPTN::setModelRotation(GLfloat _angle, glm::vec3 _modelRotateAround)
{
	modelMatrix = glm::mat4(1.0f);
	angle = _angle;
	modelRotateAround = _modelRotateAround;
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelLoaderAssimpPTN::setModelPosition(glm::vec3 _modelPosition)
{
	modelMatrix = glm::mat4(1.0f);
	modelPosition = _modelPosition;
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}
// GET
GLuint Models::ModelLoaderAssimpPTN::getNumberOfMeshes()
{
	return numberOfMeshes;
}

glm::vec3 Models::ModelLoaderAssimpPTN::getModelScale()
{
	return modelScale;
}

glm::vec3 Models::ModelLoaderAssimpPTN::getModelRotation()
{
	return modelRotateAround;
}

glm::vec3 Models::ModelLoaderAssimpPTN::getModelPosition()
{
	return modelPosition;
}
//
// RENDER MODEL
//
void Models::ModelLoaderAssimpPTN::render()
{
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs
	
	for (unsigned int i = 0; i < meshesVector.size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, meshesVector[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshesVector[i].IBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);                 // 
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

		glUseProgram(shader->getShaderProgramID()); // One shader for all meshes for now
		//
		// UPDATE UNIFORMs 
		//
		// VERTEX SHADER
		// uniform mat4 projectionMatrix in shader only once
		// uniform mat4 viewMatrix
		camera->updateCameraUniformInv(shader);
		// uniform mat4 transformationMatrix
		glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);		
		float lightPosition[] = { 0.0f, 5.0f, 15.0f };
		// uniform vec3 lightPosition
		glUniform3f(shader->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);
		// FRAGMENT SHADER
		GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };
		// uniform vec3 lightColour
		glUniform3f(shader->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
		// uniform float shineDamper
		glUniform1f(shader->getshineDamperID(), meshesVector[i].shineDamper);
		// uniform float reflectivity
		glUniform1f(shader->getreflectivityID(), meshesVector[i].reflectivity);			
		//
		// uniform sampler2D modelTexture
		//
		glUniform1i(shader->getmodelTextureID(), i); // shader textureID from each mesh connect with GL_TEXTURE0, GL_TEXTURE1...
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texturesVectorId[i]);
		//
		// DRAW MESHEs
		//
		glDrawElements(GL_TRIANGLES, meshesVector[i].numIndices, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}






