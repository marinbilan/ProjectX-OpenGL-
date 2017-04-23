//
// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
// System libs includes
#include "Includes\libsIncludes.h"
// Shaders Database [ Db ]
#include "Includes\shadersDbIncludes.h"
// Shaders [ Projection ]
#include "Includes\shadersIncludes.h"
// Camera [ View ]
#include "Includes\cameraIncludes.h"
// Models [ Model ]
#include "Includes\modelsIncludes.h"
// NEW TODO: Move separate includes
#include "Loader\if\LoaderIf.h"
#include "Loader\inc\TextureLoader.h"
#include "Loader\inc\ModelLoader.h"
#include "FBOs\Inc\WaterFBO.h"
//
// Shaders [ Projection Matrix]
//
Shaders::ShaderPTN*         shaderPTN1;        // WITHOUT NORMAL MAP
Shaders::Shader_Water_Tile* shader_Water_Tile; // WATER
Shaders::Shader_2*          shader_2;          // GUI
Shaders::Shader_3*          shader_3;          // SKYBOX
//
// Camera [ View ]
//
Camera::Camera* camera;
//
// Models
//
Models::ModelPTN*         modelVanquishTest;
Models::Model_skyBox*     model_skyBox;
Models::Model_Water_Tile* modelWaterTile;
Models::Model_GUI*        model_GUI1;
Models::Model_GUI*        model_GUI2;
//
// LIGHT
//
GLfloat light1[] = { 0.0f, 15.0f, 15.0f, 1.0f };
GLfloat light2[] = { 0.0f, 15.0f, 15.0f };
//
// LOADER
//
Loader::ModelLoader*   modelLoaderVanquish;
Loader::TextureLoader* textureLoaderVanquish;
//
// BUFFERs
//
WaterFrameBuffers* FBO1;
WaterFrameBuffers* FBO2;
//
// Variables and Constants
//
GLuint WIDTH;
GLuint HEIGHT;

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

#include "Controls\Contorls.h"
//
// LIGHT params
//
GLfloat lightPosition[] = { 0.0f, 5.0f, 15.0f };
GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };
GLfloat shineDamper = 15.0f; // def: 15.0f
GLfloat reflectivity = 1.6f; // def: 1.6

GLfloat plane1[] = { 0.0f, 1.0f, 0.0f, -0.01f };     // fbo LEFT - Render everything ABOVE
GLfloat plane2[] = { 0.0f, -1.0f, 0.0f, -0.01f };    // fbo RIGHT - Render everything BELOW
GLfloat plane3[] = { 0.0f, -1.0f, 0.0f, 100000.0f }; // HACK (glDisable doesn't work!)

GLfloat moveFactor = 0;
GLfloat WAVE_SPEED;

void RenderScene(GLfloat deltaTime)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);
	//
	// #### IMPORTANT: For each render function: ####
	//
	// 1 ] Bind VAO glBindVertexArray(VAO); 
	// 2 ] Active shader glUseProgram(ShaderID);
	// 3 ] Bind Attribs (glEnableVertexAttribArray(0), glEnableVertexAttribArray(1) ...)
	// 4 ] Update Uniform(s)
	// 5.1 ] Active Textures
	// 5.2 ] Bind Textures
	// 6 ] Render mesh (model)
	// 7 ] Disable everything

	//
	// FBO 1 [ BOTTOM LEFT GUI] texID = 8
	//
	FBO1->bindReflectionFrameBuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);
	// INVERT CAM
	GLfloat distance = 2 * (camera->getcameraPosition().y - 0.0f); // 0.0f water hight
	camera->setcameraPositionY(camera->getcameraPosition().y - distance);
	camera->invertCameraY(); 
	camera->updateCameraPosition(); // Update viewMatrix
	// RENDER skyBox from bottom camera position
	model_skyBox->renderModel();
	// RENDER vanquish from bottom camera position
	glUseProgram(shaderPTN1->getShaderProgramID());
	camera->updateCameraUniformInv(shaderPTN1); // For now update for each model - In future only once!
	glUniform4f(shaderPTN1->getplaneID(), plane1[0], plane1[1], plane1[2], plane1[3]);
	glUniform3f(shaderPTN1->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(shaderPTN1->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	modelVanquishTest->render(); //modelVanquish->render(); 
	// INVERT CAM BACK
	camera->invertCameraY();
	camera->setcameraPositionY(camera->getcameraPosition().y + distance);
	camera->updateCameraPosition();
	glBindVertexArray(0);
	glUseProgram(0);

	FBO1->unbindCurrentFrameBuffer();
	//
	// FBO 2 [ NORMAL RIGHT GUI] texID = 12
	//
	FBO2->bindRefractionFrameBuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);

	model_skyBox->renderModel();
	glUseProgram(shaderPTN1->getShaderProgramID());
	camera->updateCameraUniformInv(shaderPTN1);
	glUniform4f(shaderPTN1->getplaneID(), plane2[0], plane2[1], plane2[2], plane2[3]);
	glUniform3f(shaderPTN1->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(shaderPTN1->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	modelVanquishTest->render(); //modelVanquish->render();
	glBindVertexArray(0);
	glUseProgram(0);

	FBO2->unbindCurrentFrameBuffer();
	//
	// ----==== RENDER IN MAIN SCREEN ====----
	//
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CLIP_DISTANCE0);
	// RENDER SKYBOX
	model_skyBox->renderModel();
	// PREPARE WATER 
	WAVE_SPEED = 0.001;
	moveFactor += WAVE_SPEED;
	glUseProgram(shader_Water_Tile->getShaderProgramID());
	glUniform1f(shader_Water_Tile->getmoveFactorID(), moveFactor);
	// RENDER WATER
	modelWaterTile->renderModel();
	glUseProgram(0);
	// PREPARE VANQUISH
	glUseProgram(shaderPTN1->getShaderProgramID());
	camera->updateCameraUniformInv(shaderPTN1);
	glUniform4f(shaderPTN1->getplaneID(), plane3[0], plane3[1], plane3[2], plane3[3]);
	glUniform3f(shaderPTN1->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(shaderPTN1->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	// RENDER VANQUISH
	modelVanquishTest->render();
	glUseProgram(0);  

	// RENDERIRANJE U PROZORE
	model_GUI1->renderModel();  // FBO1 (texID = 8)
	model_GUI2->renderModel();  // FBO2 (texID = 12)

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

int main(int argc, char** argv)
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	//
	// Init GLFW
	//
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	//
	// Give me screen resolution
	//
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//
	// Initialize GLEW to setup the OpenGL Function pointers
	//
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	//
	// SHADERs [ Projection ] Initialization (only once)
	//
	shaderPTN1 = new Shaders::ShaderPTN(VSPTN, FSPTN);
	shader_Water_Tile = new Shaders::Shader_Water_Tile(VS_Water_Tile, FS_Water_Tile);
	shader_2 = new Shaders::Shader_2(VS2, FS2); // GUI
	shader_3 = new Shaders::Shader_3(VS3, FS3); // skyBox
	// Shaders Info
	std::cout << *shaderPTN1;
	std::cout << *shader_Water_Tile;
	std::cout << *shader_2;
	std::cout << *shader_3;
	//
	// CAMERA [ View ] Initialization
	//
	camera = new Camera::Camera();
	//
	// MODELS
	//
	// LOAD VANQUISH MESHs [ LOAD MESHs correct ]
	modelLoaderVanquish = new Loader::ModelLoader("_src/_models/vanquish/", "_src/_models/vanquish/modelParams.txt", shaderPTN1);
	textureLoaderVanquish = new Loader::TextureLoader();
	textureLoaderVanquish->loadVectorOfTextures2DID("_src/_models/vanquish/textures/", modelLoaderVanquish->getNumberOfMeshes());
	modelVanquishTest = new Models::ModelPTN(modelLoaderVanquish, textureLoaderVanquish, "_src/_models/vanquish/modelParams.txt", shaderPTN1);
	// SKYBOX
	model_skyBox = new Models::Model_skyBox(shader_3, camera);
	//
	// BUFFERs
	//
	FBO1 = new WaterFrameBuffers();
	FBO2 = new WaterFrameBuffers();
	std::cout << "REF TEXTURE 1: "   << FBO1->getReflectionTexture() << std::endl;
	std::cout << "REF TEXTURE 2: " << FBO2->getRefractionTexture() << std::endl;
	//meshNM = new Models::Model_AssimpNormalMap("_src/_models/barrel/", shader_7, camera, light1);
	// TO DO: clean variable names
	//model_1 = new Models::Model_1(shader_1, camera, light1);
	//
	// GUIs
	//
	model_GUI1 = new Models::Model_GUI("sword.png", shader_2, 8, glm::vec3(-0.7f, 0.5f, 0.f), glm::vec3(0.3f));
	model_GUI2 = new Models::Model_GUI("socuwan.png", shader_2, 12, glm::vec3(0.7f, 0.5f, 0.0f), glm::vec3(0.3f));
	// dudvMap
	modelWaterTile = new Models::Model_Water_Tile("_src/water/waterDUDV.png", shader_Water_Tile, camera, 8, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(14.0f));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	//
	//
	//Game loop
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
		//
		//
		//
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}