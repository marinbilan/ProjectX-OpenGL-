// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
// System libs includes
#include "Db\IncludesDb\includesDb.h"

// Shaders [ Projection Matrix]
Shaders::ShaderPTN*             shaderPTN1;        // WITHOUT NORMAL MAP
Shaders::Shader_Water_Tile*     shader_Water_Tile; // WATER
Shaders::Shader_2*              shader_2;          // GUI
Shaders::Shader_3*              shader_3;          // SKYBOX
Shaders::ShaderLearningOpenGL1* shaderOpenLearningOpenGL1;
Shaders::ShaderDepthMapFBO*     shaderDepthMapFBO1;

// Camera [ View ]
Camera::Camera* camera;

// Models
Models::ModelPTN*         modelVanquish;
Models::ModelPTN*         modelTest1;
Models::ModelPTN*         modelTest2;

Models::ModelLearnOpenGL* modelLearnOpenGL1;
Models::Model_skyBox*     model_skyBox;
Models::Model_Water_Tile* modelWaterTile;
Models::Model_GUI*        model_GUI1;
Models::Model_GUI*        model_GUI2;

// LIGHT
GLfloat light1[] = { 0.0f, 15.0f, 15.0f, 1.0f };
GLfloat light2[] = { 0.0f, 15.0f, 15.0f };

// LOADER
Loader::ModelLoader*   modelLoaderVanquish;
Loader::TextureLoader* textureLoaderVanquish;

Loader::ModelLoader*   loadModelTest1;
Loader::TextureLoader* loadTextureTest1;

// BUFFERs
FBOs::WaterFBO* waterFBO1;
FBOs::WaterFBO* waterFBO2;

FBOs::FBOShaddowMapping* FBOShadowMapping1;

// RENDERER
Renderer::Renderer* renderer;

// Variables and Constants
GLuint WIDTH;
GLuint HEIGHT;

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

#include "Controls\Contorls.h"
GLfloat planeModelPTN[] = { 0.0f, -1.0f, 0.0f, 100000.0f };    // HACK (glDisable doesn't work!)

void RenderScene(GLfloat deltaTime)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);
	//
	// RENDER INVERTED CAM 
	//
	// IMPORTANT: Render everything above (Camera is below and inverted) (Normal plane vector y = +1.0)
	waterFBO1->bindReflectionFrameBuffer(); // FBO 1 [ BOTTOM LEFT GUI] texID = 8
	camera->invertCameraDown();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);

	renderer->renderSkyBox(camera, model_skyBox);                                    // RENDER FROM BELOW ( Invert CAM )
	//renderer->renderModelPTN(planeModelPTNAbove, camera, modelVanquish, shaderPTN1); // RENDER FROM BELOW ( Invert CAM )

	waterFBO1->unbindCurrentFrameBuffer();
	camera->invertCameraUp();
	//
	// RENDER IN SHADOW MAP with shadow map shader
	//
	float near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	// Stara vrijednost zamijenjena novom testiranom camerom
	//glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	//	                              glm::vec3(0.0f, 0.0f, 0.0f),
	//	                              glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightView = glm::lookAt(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	FBOShadowMapping1->bindFBOShadowMapping();
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderDepthMapFBO1->getShaderProgramID());
	glUniformMatrix4fv(shaderDepthMapFBO1->getLightSpaceMatrixID(), 1, GL_FALSE, &lightSpaceMatrix[0][0]);
	renderer->renderDepthMap(modelTest1, shaderDepthMapFBO1); // render model with shaderDepthMapFBO1
	renderer->renderDepthMap(modelTest2, shaderDepthMapFBO1);
	FBOShadowMapping1->unbindFBOShadowMapping();
	//
	// RENDER NORMAL CAM
	//
	waterFBO1->bindRefractionFrameBuffer(); // FBO 2 [ NORMAL RIGHT GUI] texID = 12
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);

	renderer->renderSkyBox(camera, model_skyBox);
	// renderer->renderModelPTN(planeModelPTNBelow, camera, modelVanquish, shaderPTN1); // (y = -1)

	waterFBO1->unbindCurrentFrameBuffer();
	// =============================================
	// ----==== START RENDER IN MAIN SCREEN ====---- // RENDER order is IMPORTANT!
	// =============================================
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CLIP_DISTANCE0);

	renderer->renderSkyBox(camera, model_skyBox);
	renderer->renderStaticModel(glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f), camera, modelTest1, shaderPTN1);
	renderer->renderStaticModel(glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f), camera, modelTest2, shaderPTN1);
	// =============================================
	// ----==== STOP RENDER IN MAIN SCREEN ====----
	// =============================================

	// RENDER IN GUIs
	model_GUI1->renderModel();  // FBO1 (texID = 8) TODO Hardcoded numbers
	// model_GUI2->renderModel();  // FBO2 (texID = 12) TODO

	// ----==== RENDER NORMAL MAP MODEL ====----
	// glBindVertexArray(6);
	// glUseProgram(18);
	//m_pMesh->Render();
	//mesh_Assimp->Render();
	//glUniform1i(shader_7->getmodelTextureID(), 0); // order texture connect with GL_TEXTURE0
	//glUniform1i(shader_7->getnormalMapID(), 1);    // normal map texture connect with GL_TEXTURE1
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, 5); // order texture TextureID = 5
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, 6);  // normal map texture TextureID = 6
    //meshNM->Render();
	//glBindVertexArray(0);
	//glUseProgram(0);
	//model_6->renderModel();	
	// WARNING: UPDATE UNIFORM(s)
	//glUniformMatrix4fv(shader_3->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);	
	//model_1->renderModel();

	// ----==== CLOCK ====----
	//std::clock_t start = std::clock();
	//double duration;
	//std::clock_t end = std::clock();
	//duration = (end - start) / (double)CLOCKS_PER_SEC;
	//std::cout << "Trajanje algoritma: " << duration << std::endl;
}

void get_resolution() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	WIDTH = mode->width;
	HEIGHT = mode->height;
}

void characterModCallback(GLFWwindow* window, unsigned int keyCode, int modifierKey) 
{
	if (keyCode == 43)
	{	
		std::cout << "> ";
		std::string stringKey;	
		std::getline(std::cin, stringKey);
	}
}

void RenderSceneMaster(GLfloat deltaTime);

int main(int argc, char** argv)
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	// Give me screen resolution
	get_resolution(); 
	std::cout << WIDTH << " " << HEIGHT << std::endl;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3Ddev", nullptr, nullptr); // 4th parameter = glfwGetPrimaryMonitor() for fullscreen

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetCharModsCallback(window, characterModCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	// SHADERs [ Projection ] Initialization (only once)
	shaderPTN1 = new Shaders::ShaderPTN("shaderPTN1", VSPTN, FSPTN);
	shader_Water_Tile = new Shaders::Shader_Water_Tile(VS_Water_Tile, FS_Water_Tile);
	shader_2 = new Shaders::Shader_2(VS2, FS2); // GUI
	shader_3 = new Shaders::Shader_3(VS3, FS3); // skyBox
	shaderOpenLearningOpenGL1 = new Shaders::ShaderLearningOpenGL1(VSLearningOpenGL1, FSLearningOpenGL1);
	shaderDepthMapFBO1 = new Shaders::ShaderDepthMapFBO(VSDepthMapFBO, FSDepthMapFBO);
	// SHADERs INFO
	std::cout << *shaderDepthMapFBO1;
	// CAMERA [ViewMatrix] INIT
	camera = new Camera::Camera(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Current Light position
	// MODELS
	modelTest1 = new Models::ModelPTN("_src/_models/cubeNM/",
		"cube",
		loadModelTest1, 
		loadTextureTest1, 
		shaderPTN1, 
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(0.01f, 0.01f, 0.001f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		-1.55f);

	modelTest2 = new Models::ModelPTN("_src/_models/cubeNM/",
		"cube", 
		loadModelTest1, 
		loadTextureTest1, 
		shaderPTN1, 
		glm::vec3(0.0f, 0.2f, 0.0f), 
		glm::vec3(0.001f, 0.001f, 0.001f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		-1.55f);
	// SKYBOX
	model_skyBox = new Models::Model_skyBox(shader_3, camera);
	// BUFFERs
	waterFBO1 = new FBOs::WaterFBO();
	waterFBO2 = new FBOs::WaterFBO();
	FBOShadowMapping1 = new FBOs::FBOShaddowMapping(380, 180, WIDTH, HEIGHT);
	//meshNM = new Models::Model_AssimpNormalMap("_src/_models/barrel/", shader_7, camera, light1);
	// TO DO: clean variable names
	//model_1 = new Models::Model_1(shader_1, camera, light1);
	//
	// GUIs
	//
	model_GUI1 = new Models::Model_GUI("sword.png", shader_2, FBOShadowMapping1->getFBOShadowMapTextureID(), glm::vec3(-0.7f, 0.5f, 0.f), glm::vec3(0.3f));
	model_GUI2 = new Models::Model_GUI("socuwan.png", shader_2, 9, glm::vec3(0.7f, 0.5f, 0.0f), glm::vec3(0.3));
	// dudvMap
	modelWaterTile = new Models::Model_Water_Tile("_src/water/waterDUDV.png", shader_Water_Tile, camera, 8, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(14.0f));
	//
	// RENDERER
	//
	renderer = new Renderer::Renderer();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	//
	//
	// GAME LOOP
	//
	//
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();
		//
		// RENDER SCENE
		//
		RenderScene(deltaTime);
		//RenderSceneMaster(deltaTime);
		//
		//
		//
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void RenderSceneMaster(GLfloat deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);

	renderer->renderStaticModel(glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f), camera, modelTest1, shaderPTN1);
}