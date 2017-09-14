//#ifndef MODELLOADERASSIMPPTNANIM__
//#define MODELLOADERASSIMPPTNANIM__
//#include <map>
//
////
//// ModelIf
////
//#include "../if/ModelIf.h"
//
//#include "ogldev_lib\ogldev_util.h" // OK
////#include "ogldev_lib\ogldev_math_3d.h"
////#include "ogldev_lib\matrix4x4.h"
////#include "ogldev_lib\ogldev_texture.h"
//
//namespace Models
//{
//struct VertexAnim
//{
//	glm::vec3 position;
//	glm::vec2 textureCoord;
//	glm::vec3 normal;
//
//	VertexAnim() {}
//
//	VertexAnim(glm::vec3& _position, glm::vec2& _textureCoord, glm::vec3& _normal)
//	{
//		position     = _position;
//		textureCoord = _textureCoord;
//		normal       = _normal;
//	}
//};
//struct Edge
//{
//	Edge(GLuint _a, GLuint _b)
//	{
//		assert(_a != _b);
//
//		if (_a < _b)
//		{
//			a = _a;
//			b = _b;
//		}
//		else
//		{
//			a = _b;
//			b = _a;
//		}
//	}
//
//	void Print()
//	{
//		printf("Edge %d %d\n", a, b);
//	}
//
//	GLuint a;
//	GLuint b;
//};
//
//struct Neighbors
//{
//	uint n1;
//	uint n2;
//
//	Neighbors()
//	{
//		n1 = n2 = (uint)-1;
//	}
//
//	void AddNeigbor(uint n)
//	{
//		if (n1 == -1) {
//			n1 = n;
//		}
//		else if (n2 == -1) {
//			n2 = n;
//		}
//		else {
//			assert(0);
//		}
//	}
//
//	uint GetOther(uint me) const
//	{
//		if (n1 == me) {
//			return n2;
//		}
//		else if (n2 == me) {
//			return n1;
//		}
//		else {
//			assert(0);
//		}
//
//		return 0;
//	}
//};
//
//
//struct CompareEdges
//{
//	bool operator()(const Edge& Edge1, const Edge& Edge2)
//	{
//		if (Edge1.a < Edge2.a) {
//			return true;
//		}
//		else if (Edge1.a == Edge2.a) {
//			return (Edge1.b < Edge2.b);
//		}
//		else {
//			return false;
//		}
//	}
//};
//
//
//struct CompareVectors
//{
//	bool operator()(const aiVector3D& a, const aiVector3D& b)
//	{
//		if (a.x < b.x) {
//			return true;
//		}
//		else if (a.x == b.x) {
//			if (a.y < b.y) {
//				return true;
//			}
//			else if (a.y == b.y) {
//				if (a.z < b.z) {
//					return true;
//				}
//			}
//		}
//
//		return false;
//	}
//};
//
//struct Face
//{
//	GLuint Indices[3];
//
//	GLuint GetOppositeIndex(const Edge& e) const
//	{
//		for (GLuint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(Indices); i++) {
//			GLuint Index = Indices[i];
//
//			if (Index != e.a && Index != e.b) {
//				return Index;
//			}
//		}
//
//		assert(0);
//
//		return 0;
//	}
//};
//
//class ModelLoaderAssimpPTNAnim : public ModelsIf::ModelsIf
//{
//public:
//	//
//	// CONSTRUCTORs / DESTRUCTORs
//	//
//	ModelLoaderAssimpPTNAnim(char*                          _modelPath,
//		                 Texture::TextureIf::TextureIf* _textureLoader,
//		                 char*                          _textureShaderParams,
//				         Shaders::ShadersIf::ShadersIf* _shader, 
//				         Camera::CameraIf::CameraIf*    _camera,    
//				         GLfloat*                       _light,
//		                 bool WithAdjacencies);
//
//	~ModelLoaderAssimpPTNAnim();
//
//	glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from)
//	{
//		glm::mat4 to;
//
//
//		to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
//		to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
//		to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
//		to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;
//
//		return to;
//	}
//
//	glm::mat3 aiMatrix3x3ToGlm(const aiMatrix3x3* from)
//	{
//		glm::mat3 to;
//
//
//		to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1;
//		to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2;
//		to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3;
//
//		return to;
//	}
//	//
//	// OPERATORs
//	//
//	friend std::ostream& operator<<(std::ostream& output, ModelLoaderAssimpPTNAnim& info)
//	{
//		return output;
//	}
//	
//private:
//	#define NUM_BONES_PER_VEREX 4
//
//	struct BoneInfo
//	{
//		glm::mat4 BoneOffset;
//		glm::mat4 FinalTransformation;
//
//		BoneInfo()
//		{
//			//BoneOffset.SetZero();
//			//FinalTransformation.SetZero();
//		}
//	};
//	struct VertexBoneData
//	{
//		GLuint IDs[NUM_BONES_PER_VEREX];
//		static std::vector<GLuint> IDss; // ALT
//		
//		float Weights[NUM_BONES_PER_VEREX];
//
//		VertexBoneData()
//		{
//			//IDss.resize(NUM_BONES_PER_VEREX);
//			Reset();
//		};
//
//		void Reset()
//		{
//			
//			//ZERO_MEM(IDs);
//			//ZERO_MEM(Weights);
//		}
//
//		void AddBoneData(GLuint BoneID, float Weight);
//	};
//	//
//	// FUNCTIONs
//	// 
//	virtual bool InitFromScene(const aiScene* _pScene);
//	//static GLuint Models::ModelLoaderAssimpPTNAnim::GetOppositeIndex(const aiFace& Face/*, const Edge& e*/);
//	virtual void FindAdjacencies(const aiMesh* paiMesh, std::vector<unsigned int>& Indices);
//	virtual void InitMesh(GLuint MeshIndex,
//		const aiMesh* paiMesh,
//		std::vector<glm::vec3>& Positions,
//		std::vector<glm::vec3>& Normals,
//		std::vector<glm::vec2>& TexCoords,
//		std::vector<VertexBoneData>& Bones,
//		std::vector<GLuint>& Indices);
//	//virtual void VertexBoneData::AddBoneData(GLuint BoneID, float Weight);
//	virtual void LoadBones(GLuint MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);
//	virtual void Render();
//	virtual GLuint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual GLuint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual GLuint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//	virtual void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
//	virtual void BoneTransform(float TimeInSeconds, std::vector<glm::mat4>& Transforms);
//	virtual const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
//
//	enum VB_TYPES {
//		INDEX_BUFFER,
//		POS_VB,
//		NORMAL_VB,
//		TEXCOORD_VB,
//		BONE_VB,
//		NUM_VBs
//	};
//
//	GLuint VAO;
//	GLuint m_Buffers[NUM_VBs];
//	std::vector<GLuint> m_BuffersV; // ALT
//
//	struct MeshEntry {
//
//		void init(std::vector<VertexAnim>& _vertices, std::vector<unsigned int>& _indices);
//
//		//GLuint VAO;
//		GLuint VBO;
//		GLuint IBO;
//
//		GLuint numIndices;
//		//
//		// MESH SHADER PARAMs
//		//
//		GLfloat shineDamper;
//		GLfloat reflectivity;
//
//		unsigned int NumIndices;
//		unsigned int BaseVertex;
//		unsigned int BaseIndex;
//		unsigned int MaterialIndex;
//	};
//	std::map<std::string, GLuint> m_BoneMapping; // maps a bone name to its index
//	GLuint m_NumBones;
//	std::vector<BoneInfo> m_BoneInfo;
//
//	glm::mat4 modelMatrix;
//	glm::mat4 m_GlobalInverseTransform;
//	//
//	// CONSTRUCTOR
//	//
//	char*                          modelPath;
//	Texture::TextureIf::TextureIf* textureLoader;
//	char*                          textureShaderParams;
//	Shaders::ShadersIf::ShadersIf* shader;
//	Camera::CameraIf::CameraIf*    camera;	
//	GLfloat*                       light;
//
//	std::vector<GLuint>            texturesVectorId;
//	//
//	// MODEL VARIABLE	
//	//
//
//	std::vector<MeshEntry> meshesVector;
//
//	const aiScene*   pScene;
//	Assimp::Importer m_Importer;
//
//	std::map<Edge, Neighbors, CompareEdges> m_indexMap;
//	std::map<aiVector3D, uint, CompareVectors> m_posMap;
//	std::vector<Face> m_uniqueFaces;
//	bool m_withAdjacencies;
//	Assimp::Importer Importer;
//};
//}
//
//#endif
