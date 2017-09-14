//#include "../../Models/inc/ModelLoaderAssimpPTNAnim.h"
//
//#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//#define POSITION_LOCATION    0
//#define TEX_COORD_LOCATION   1
//#define NORMAL_LOCATION      2
//#define BONE_ID_LOCATION     3
//#define BONE_WEIGHT_LOCATION 4
////
////
//// CONSTRUCTORs / DESTRUCTOR(s)
////
////
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::VertexBoneData::AddBoneData(GLuint BoneID, float Weight)
//{
//	for (GLuint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++) { // Hardcoden NUM_BONES_PER_VEREX
//		if (Weights[i] == 0.0) {
//			IDs[i] = BoneID;
//			Weights[i] = Weight;
//			return;
//		}
//	}
//
//	// should never get here - more bones than we have space for
//	assert(0);
//}
//// DONE!
//Models::ModelLoaderAssimpPTNAnim::ModelLoaderAssimpPTNAnim(char*                          _modelPath,
//	                                                       Texture::TextureIf::TextureIf* _textureLoader,
//	                                                       char*                          _textureShaderParams,
//								                           Shaders::ShadersIf::ShadersIf* _shader, 
//								                           Camera::CameraIf::CameraIf*    _camera, 
//								                           GLfloat*                       _light,
//														   bool WithAdjacencies)
//{
//	m_withAdjacencies = WithAdjacencies;
//
//	modelMatrix = glm::mat4(1.0f); // REMOVE
//
//	VAO = 0;
//	ZERO_MEM(m_Buffers); // CHECK
//	m_NumBones = 0;
//	pScene = NULL;
//	m_withAdjacencies = false;
//
//	// MY STUFF
//	modelPath = _modelPath;
//	textureLoader = _textureLoader;
//	textureShaderParams = _textureShaderParams;
//	shader = _shader;
//	camera = _camera;
//	light = _light;	
//	//
//	// CREATE MODEL
//	//
//	// Create the VAO
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	// Create the buffers for the vertices attributes	
//	glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers); // CHECK
//
//	bool Ret = false;
//	//Assimp::Importer Importer; // REMOVED in .h
//	const std::string model = "model.3ds";
//
//	pScene = Importer.ReadFile(modelPath + model, aiProcess_Triangulate | 
//		                                          aiProcess_GenSmoothNormals | 
//		                                          aiProcess_FlipUVs | 
//		                                          aiProcess_JoinIdenticalVertices);
//	if (pScene) 
//	{
//		std::cout << "pScene->mNumMeshes: " << pScene->mNumMeshes << std::endl;
//		//
//		// Load Textures
//		//
//		// NEW
//		 m_GlobalInverseTransform = aiMatrix4x4ToGlm(&pScene->mRootNode->mTransformation);
//		 m_GlobalInverseTransform = glm::inverse(m_GlobalInverseTransform);
//		//
//		// texturesVectorId = textureLoader->loadtexture2DVectorIDs(modelPath, pScene->mNumMeshes);
//		Ret = initFromScene(pScene);
//	}
//	else 
//	{
//		std::cout << "Error parsing: " << modelPath << " " << model << " " << Importer.GetErrorString() << std::endl;
//	}	
//}
//
//Models::ModelLoaderAssimpPTNAnim::~ModelLoaderAssimpPTNAnim()
//{
//	std::cout << "ModelLoaderAssimpPNT destructor called!" << std::endl;
//}
////
//// FUNCTION(s) - Add Clean function
////
//// DONE!
//bool Models::ModelLoaderAssimpPTNAnim::InitFromScene(const aiScene* _pScene)
//{	
//	meshesVector.resize(_pScene->mNumMeshes); // meshesVector = m_Entries
//	// Textures from file
//
//	std::vector<glm::vec3> Positions;
//	std::vector<glm::vec3> Normals;
//	std::vector<glm::vec2> TexCoords;
//	std::vector<VertexBoneData> Bones;
//	std::vector<GLuint> Indices;
//
//	GLuint NumVertices = 0;
//	GLuint NumIndices = 0;
//
//	GLuint VerticesPerPrim = m_withAdjacencies ? 6 : 3;
//
//	// Count the number of vertices and indices
//	for (GLuint i = 0; i < meshesVector.size(); i++) {
//		meshesVector[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
//		meshesVector[i].NumIndices = pScene->mMeshes[i]->mNumFaces * VerticesPerPrim;
//		meshesVector[i].BaseVertex = NumVertices;
//		meshesVector[i].BaseIndex = NumIndices;
//
//		NumVertices += pScene->mMeshes[i]->mNumVertices;
//		NumIndices += meshesVector[i].NumIndices;
//	}
//
//	// Reserve space in the vectors for the vertex attributes and indices
//	Positions.reserve(NumVertices);
//	Normals.reserve(NumVertices);
//	TexCoords.reserve(NumVertices);
//	Bones.resize(NumVertices);
//	Indices.reserve(NumIndices);
//
//	// InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices); // OLD STUFF
//
//	std::ifstream modelParams(textureShaderParams);
//	std::string str;
//
//	// Initialize the meshes in the scene one by one
//	for (unsigned int i = 0; i < meshesVector.size(); i++) {
//		const aiMesh* paiMesh = _pScene->mMeshes[i];
//		// Read each line from modelParams File
//		std::getline(modelParams, str);
//		// INIT EACH MESH
//		//initMesh(i, paiMesh);
//		InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
//		// Read params for each mesh in meshVector
//		std::istringstream buf(str);
//		for (std::string word; buf >> word;)
//		{
//			if (word == "shineDamper")
//			{
//				buf >> word;
//				meshesVector[i].shineDamper = atof(word.c_str());
//				std::cout << meshesVector[i].shineDamper;
//			}
//			if (word == "reflectivity")
//			{
//				buf >> word;
//				meshesVector[i].reflectivity = atof(word.c_str());
//				std::cout << meshesVector[i].reflectivity;
//			}
//		}
//		std::cout << std::endl;
//	}
//
//	// Generate and populate the buffers with vertex attributes and the indices
//	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(POSITION_LOCATION);
//	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(TEX_COORD_LOCATION);
//	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(NORMAL_LOCATION);
//	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(BONE_ID_LOCATION);
//	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
//	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
//	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
//
//	return true;
//}
//// DONE!
//static GLuint GetOppositeIndex(const aiFace& Face, const Models::Edge& e)
//{
//	for (GLuint i = 0; i < 3; i++) {
//		GLuint Index = Face.mIndices[i];
//
//		if (Index != e.a && Index != e.b) {
//			return Index;
//		}
//	}
//
//	assert(0);
//
//	return 0;
//}
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::FindAdjacencies(const aiMesh* paiMesh, std::vector<unsigned int>& Indices)
//{
//	// Step 1 - find the two triangles that share every edge
//	for (GLuint i = 0; i < paiMesh->mNumFaces; i++) {
//		const aiFace& face = paiMesh->mFaces[i];
//
//		Face Unique;
//
//		// If a position vector is duplicated in the VB we fetch the 
//		// index of the first occurrence.
//		for (uint j = 0; j < 3; j++) {
//			uint Index = face.mIndices[j];
//			aiVector3D& v = paiMesh->mVertices[Index];
//
//			if (m_posMap.find(v) == m_posMap.end()) {
//				m_posMap[v] = Index;
//			}
//			else {
//				Index = m_posMap[v];
//			}
//
//			Unique.Indices[j] = Index;
//		}
//
//		m_uniqueFaces.push_back(Unique);
//
//		Edge e1(Unique.Indices[0], Unique.Indices[1]);
//		Edge e2(Unique.Indices[1], Unique.Indices[2]);
//		Edge e3(Unique.Indices[2], Unique.Indices[0]);
//
//		m_indexMap[e1].AddNeigbor(i);
//		m_indexMap[e2].AddNeigbor(i);
//		m_indexMap[e3].AddNeigbor(i);
//	}
//
//	// Step 2 - build the index buffer with the adjacency info
//	for (uint i = 0; i < paiMesh->mNumFaces; i++) {
//		const Face& face = m_uniqueFaces[i];
//
//		for (uint j = 0; j < 3; j++) {
//			Edge e(face.Indices[j], face.Indices[(j + 1) % 3]);
//			assert(m_indexMap.find(e) != m_indexMap.end());
//			Neighbors n = m_indexMap[e];
//			uint OtherTri = n.GetOther(i);
//
//			assert(OtherTri != -1);
//
//			const Face& OtherFace = m_uniqueFaces[OtherTri];
//			uint OppositeIndex = OtherFace.GetOppositeIndex(e);
//
//			Indices.push_back(face.Indices[j]);
//			Indices.push_back(OppositeIndex);
//		}
//	}
//}
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::InitMesh(GLuint MeshIndex,
//												const aiMesh* paiMesh,
//												std::vector<glm::vec3>& Positions,
//												std::vector<glm::vec3>& Normals,
//												std::vector<glm::vec2>& TexCoords,
//												std::vector<VertexBoneData>& Bones,
//												std::vector<GLuint>& Indices)
//{
//	//std::vector<VertexAnim>   vertices; // PER MESH
//	//std::vector<unsigned int> indices;  // PER MESH
//
//	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
//
//	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
//		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
//		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
//		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
//
//		//VertexAnim v(glm::vec3(pPos->x, pPos->y, pPos->z),
//		//	         glm::vec2(pTexCoord->x, pTexCoord->y),
//		//	         glm::vec3(pNormal->x, pNormal->y, pNormal->z));
//
//		//vertices.push_back(v);
//		Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
//		Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
//		TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
//	}
//
//	//for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++) {
//	//	const aiFace& Face = _paiMesh->mFaces[i];
//	//	assert(Face.mNumIndices == 3);
//	//	indices.push_back(Face.mIndices[0]);
//	//	indices.push_back(Face.mIndices[1]);
//	//	indices.push_back(Face.mIndices[2]);
//	//}
//
//	//meshesVector[_index].init(vertices, indices);
//
//	LoadBones(MeshIndex, paiMesh, Bones);
//
//	if (m_withAdjacencies) {
//		FindAdjacencies(paiMesh, Indices); // Let's assume no need now
//	}
//	else {
//		// Populate the index buffer
//		for (GLuint i = 0; i < paiMesh->mNumFaces; i++) {
//			const aiFace& Face = paiMesh->mFaces[i];
//			assert(Face.mNumIndices == 3);
//			Indices.push_back(Face.mIndices[0]);
//			Indices.push_back(Face.mIndices[1]);
//			Indices.push_back(Face.mIndices[2]);
//		}
//	}
//}
//
//
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::LoadBones(GLuint MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
//{
//	for (GLuint i = 0; i < pMesh->mNumBones; i++) {
//		GLuint BoneIndex = 0;
//		std::string BoneName(pMesh->mBones[i]->mName.data);
//
//		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
//			// Allocate an index for a new bone
//			BoneIndex = m_NumBones;
//			m_NumBones++;
//			BoneInfo bi;
//			m_BoneInfo.push_back(bi);
//			m_BoneInfo[BoneIndex].BoneOffset = aiMatrix4x4ToGlm(&pMesh->mBones[i]->mOffsetMatrix);
//			m_BoneMapping[BoneName] = BoneIndex;
//		}
//		else {
//			BoneIndex = m_BoneMapping[BoneName];
//		}
//
//		for (GLuint j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
//			GLuint VertexID = meshesVector[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
//			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
//			Bones[VertexID].AddBoneData(BoneIndex, Weight); // DONE!
//		}
//	}
//}
//
//void Models::ModelLoaderAssimpPTNAnim::Render()
//{
//	//glBindVertexArray(m_VAO);
//
//	//uint Topology = m_withAdjacencies ? GL_TRIANGLES_ADJACENCY : GL_TRIANGLES;
//
//	//for (uint i = 0; i < m_Entries.size(); i++) {
//	//	const uint MaterialIndex = m_Entries[i].MaterialIndex;
//
//	//	assert(MaterialIndex < m_Textures.size());
//
//	//	if (m_Textures[MaterialIndex]) {
//	//		m_Textures[MaterialIndex]->Bind(COLOR_TEXTURE_UNIT);
//	//	}
//
//	//	glDrawElementsBaseVertex(Topology,
//	//		m_Entries[i].NumIndices,
//	//		GL_UNSIGNED_INT,
//	//		(void*)(sizeof(uint) * m_Entries[i].BaseIndex),
//	//		m_Entries[i].BaseVertex);
//	//}
//
//	//// Make sure the VAO is not changed from the outside    
//	//glBindVertexArray(0);
//}
////
////
////
//// DONE!
//GLuint Models::ModelLoaderAssimpPTNAnim::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	for (GLuint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
//		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
//			return i;
//		}
//	}
//
//	assert(0);
//
//	return 0;
//}
//// DONE!
//GLuint Models::ModelLoaderAssimpPTNAnim::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	assert(pNodeAnim->mNumRotationKeys > 0);
//
//	for (GLuint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
//		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
//			return i;
//		}
//	}
//
//	assert(0);
//
//	return 0;
//}
//// DONE!
//GLuint Models::ModelLoaderAssimpPTNAnim::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	assert(pNodeAnim->mNumScalingKeys > 0);
//
//	for (GLuint i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
//		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
//			return i;
//		}
//	}
//
//	assert(0);
//
//	return 0;
//}
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	if (pNodeAnim->mNumPositionKeys == 1) {
//		Out = pNodeAnim->mPositionKeys[0].mValue;
//		return;
//	}
//
//	GLuint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
//	GLuint NextPositionIndex = (PositionIndex + 1);
//	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
//	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
//	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
//	assert(Factor >= 0.0f && Factor <= 1.0f);
//	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
//	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
//	aiVector3D Delta = End - Start;
//	Out = Start + Factor * Delta;
//}
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	// we need at least two values to interpolate...
//	if (pNodeAnim->mNumRotationKeys == 1) {
//		Out = pNodeAnim->mRotationKeys[0].mValue;
//		return;
//	}
//
//	GLuint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
//	GLuint NextRotationIndex = (RotationIndex + 1);
//	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
//	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
//	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
//	assert(Factor >= 0.0f && Factor <= 1.0f);
//	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
//	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
//	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
//	Out = Out.Normalize();
//}
//// DONE!
//void  Models::ModelLoaderAssimpPTNAnim::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	if (pNodeAnim->mNumScalingKeys == 1) {
//		Out = pNodeAnim->mScalingKeys[0].mValue;
//		return;
//	}
//
//	GLuint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
//	GLuint NextScalingIndex = (ScalingIndex + 1);
//	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
//	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
//	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
//	assert(Factor >= 0.0f && Factor <= 1.0f);
//	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
//	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
//	aiVector3D Delta = End - Start;
//	Out = Start + Factor * Delta;
//}
//// IMPLEMENTATION in progress
//void Models::ModelLoaderAssimpPTNAnim::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform)
//{
//	std::string NodeName(pNode->mName.data);
//
//	const aiAnimation* pAnimation = pScene->mAnimations[0];
//
//	// Matrix4f NodeTransformation(pNode->mTransformation);
//	glm::mat4 NodeTransformation(aiMatrix4x4ToGlm(&pNode->mTransformation));
//
//	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
//
//	if (pNodeAnim) {
//		// Interpolate scaling and generate scaling transformation matrix
//		aiVector3D Scaling;
//		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim); // IMPL
//		// TO DO:
//		// Matrix4f ScalingM;
//		glm::mat4 ScalingM;
//		// ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);
//
//		// Interpolate rotation and generate rotation transformation matrix
//		aiQuaternion RotationQ;
//		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
//		// TO DO: CHECK CAREFULLY
//		// Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());
//		glm::mat3 RotationM = aiMatrix3x3ToGlm(&RotationQ.GetMatrix());
//
//		// TO DO:
//		// Interpolate translation and generate translation transformation matrix
//		aiVector3D Translation;
//		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
//		// Matrix4f TranslationM;
//		glm::mat4 TranslationM;
//		// TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);
//
//		// TO DO:
//		// Combine the above transformations
//		// NodeTransformation = TranslationM * RotationM * ScalingM;
//	}
//
//	//Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;
//
//	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
//		GLuint BoneIndex = m_BoneMapping[NodeName];
//		// m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
//	}
//
//	for (GLuint i = 0; i < pNode->mNumChildren; i++) {
//		// ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
//	}
//}
//// DONE!
//void Models::ModelLoaderAssimpPTNAnim::BoneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms)
//{
//	// Matrix4f Identity;
//	// Identity.InitIdentity();
//	glm::mat4 Identity = glm::mat4(1.0); // set identity
//
//	float TicksPerSecond = (float)(pScene->mAnimations[0]->mTicksPerSecond != 0 ? pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
//	float TimeInTicks = TimeInSeconds * TicksPerSecond;
//	float AnimationTime = fmod(TimeInTicks, (float)pScene->mAnimations[0]->mDuration);
//
//	ReadNodeHeirarchy(AnimationTime, pScene->mRootNode, Identity);
//
//	Transforms.resize(m_NumBones);
//
//	for (GLuint i = 0; i < m_NumBones; i++) {
//		Transforms[i] = m_BoneInfo[i].FinalTransformation;
//	}
//}
//// DONE!
//const aiNodeAnim* Models::ModelLoaderAssimpPTNAnim::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
//{
//	for (GLuint i = 0; i < pAnimation->mNumChannels; i++) {
//		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
//
//		if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
//			return pNodeAnim;
//		}
//	}
//
//	return NULL;
//}
//
//
