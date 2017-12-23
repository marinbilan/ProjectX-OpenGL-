// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"
// SHADERS DB
#include "..\..\Db\ShadersDb\shadersDB.h"

// SHADERS [ Projection ]
#include "Shaders\if\ShaderIf.h"

#include "Shaders\inc\ShaderSkyBox0.h"
#include "Shaders\inc\ShaderWaterTile0.h"
#include "Shaders\inc\ShaderLearningOpenGL0.h"
#include "Shaders\inc\ShaderPTN0.h"
#include "Shaders\inc\ShaderPTN1.h"
#include "Shaders\inc\ShaderNormalMapPTNT0.h"
#include "Shaders\inc\ShaderGUI0.h"
#include "Shaders\inc\ShaderTerrain0.h"
#include "Shaders\inc\ShaderMarker0.h"

// CAMERA [ View ]
#include "Camera\if\CameraIf.h"

#include "Camera\inc\Camera.h"
// MODELs [ Model ]
#include "Models\if\ModelIf.h"

#include "Models\inc\ModelSkyBox0.h"
#include "Models\inc\ModelTerrain0.h"
#include "Models\inc\ModelWaterTile0.h"
#include "Models\inc\ModelLearnOpenGL0.h"
#include "Models\inc\ModelPTN0.h"
#include "Models\inc\ModelGUI0.h"
// LOADER
#include "Loader\if\LoaderIf.h"

#include "Loader\inc\TextureLoader.h"
#include "Loader\inc\ModelLoader.h"
#include "Loader\inc\ModelLoaderLearningOpenGL.h"
#include "FBOs\inc\WaterFBO.h"
// RENDERER
#include "Renderer\inc\Renderer.h"
// COMMAND PROMPT
#include "CommonFunctions/CommandPrompt.h"
// FBO
#include "FBOs\if\FBOIf.h"

#include "FBOs\inc\FBOShaddowMapping.h"

// #include <utility>
//#include <memory>
// using std::unique_ptr;
// CONTROLS
// +--------------------------+
// | APPLICATION ARCHITECTURE |
// +--------------------------+
//                        
//                                                                                               +-----------------+                       
//                                                                                               | CommonFunctions |                      
//                                                                                               +-----------------+                             
//                                                                                                        |
//                                                  +-----------------------------------------------------+------------------------------------------------------+
//                                                  |                                                     |                                                      |
//                                            #include "../../CommonFunctions/CommonFunctions.h"    #include "../../CommonFunctions/CommonFunctions.h"    #include "../../CommonFunctions/CommonFunctions.h"
//                                            +------------+                                        +------------+                                        +------------+
//                                            | [LoaderIf] |                                        | [ShaderIf] |                                        | [CameraIf] |
//                                            +------------+                                        +------------+                                        +------------+
//                                                  |                                                     | |                                                    | |
//                                  +----------------------------+                                        | |                                                    | |
//                                  |                            |                                        | |                                                    | |
//                        -----------------------------  -----------------                           -------------                                           ----------
//                        [ ModelLoaderLearningOpenGL ]  [ TextureLoader ]                           [ ShaderPTN ]                                           [ Camera ]
//                        -----------------------------  -----------------                           -------------                                           ----------
//                                  |                            |                                          |                                                      |     
//                                  |                            |                                          |                                                      |
//                                  +----------------------------+                                          |                                                      |
//                                                 |                                                        |                                                      |
//                                                 |                                                        |                                                      |
//                                  #include "..ModelLoaderLearningOpenGL.h"                                |                                                      |
//                                  #include "..TextureLoader.h"                                            |                                                      |
//                                           +-----------+                                                  |                                                      |
//                                           | [ModelIf] |                                                  |                                                      |
//                                           +-----------+                                                  |                                                      |
//                                                 | |                                                      |                                                      |
//                                             ------------                                                 |                                                      |
//                                             [ ModelPTN ]                                                 |                                                      |
//                                             ------------                                                 |                                                      |
//                                                   |                                                      |                                                      |
//                                                   +------------------------------------------------------+------------------------------------------------------+
//                                                                                                          |                                                       
//                                           #include glew                                                  |                                                      
//									         #include glfw                                                  |                                                      
//                                           #include glm                                                   +---------------------+
//                                           #include "..shadersDB.h" // GLSL Programs                      |                     | 
//                                           // SHADERs                                                     |                     |
//                                           #include "Shaders\if\ShaderIf.h"                               |               #include "..\..\Camera\if\CameraIf.h"
//						                     #include "Shaders\inc\ShaderPTN.h"                             |               #include "..\..\Shaders\if\ShaderIf.h"
//                                           // CAMERAs                                                     |               #include "..\..\Models\if\ModelIf.h"
//                                           #include "Camera\if\CameraIf.h"                                |                     |
//                                           #include "Camera\inc\Camera.h"                                 |               +--------------+
//                                           // LOADER                                                      |               | [RendererIf] |
//                                           #include "Loader\if\LoaderIf.h"                                |               +--------------+
//                                           #include "Loader\inc\ModelLoader.h"                            |                     |
//                                           #include "Loader\inc\TextureLoader.h"                          |                     |
//                                           // MODEL                                                       |                     |
//                                           #include "Models\if\ModelIf.h"                                 |                     |
//                                           #include "Models\inc\ModelPTN.h"                               |                     |
//									         // RENDERER                                                    |                     |
//							                 #include "Renderer\inc\Renderer.h"                             |                     |
//							                 #include "#include "CommonFunctions/CommandPrompt.h"           |                     |
//                                           +------------------+                                           |                     |
//                                           | ProjectX [OpenGL]| <-----------------------------------------+---------------------+
//						                     +------------------+
//
// Shaders [ Projection ]
Shaders::ShaderSkyBox0*         shaderSkyBox00;    // SKYBOX
Shaders::ShaderWaterTile0*      shaderWaterTile00; // WATER    
Shaders::ShaderGUI0*            shaderGUI00;       // GUI
Shaders::ShaderTerrain0*        shaderTerrain00;
// Camera [ View ]
Camera::Camera* camera;
// FBOs
FBOs::WaterFBO* waterFBO1;
FBOs::WaterFBO* waterFBO2;
// Models [ Model ]
Models::ModelSkyBox0*     modelSkyBox00;
Models::ModelWaterTile0*  modelWaterTile00;
Models::ModelGUI0*        modelGUI00;
Models::ModelGUI0*        modelGUI01;
Models::ModelTerrain0*    modelTerrain00;

Renderer::Renderer* renderer;
GLuint WIDTH;
GLuint HEIGHT;
GLfloat deltaTime = 0.0f; 
GLfloat lastFrame = 0.0f; 
#include "Controls\Contorls.h"
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

	//renderer->renderSkyBox(camera, model_skyBox);                                    // RENDER FROM BELOW ( Invert CAM )
	//renderer->renderModelPTN(planeModelPTNAbove, camera, modelVanquish, shaderPTN1); // RENDER FROM BELOW ( Invert CAM )

	waterFBO1->unbindCurrentFrameBuffer();
	camera->invertCameraUp();
	//
	// RENDER IN SHADOW MAP with shadow map shader
	//
	// -------------------------------- FRAME DEPTH BUFFER ----------------------------------------------
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT); // Clear any data from last frame. No need to clear COLOR BUFFER because there is no attach for COLOR BUFFER
	// FBOShadowMapping1->bindFBOShadowMapping();

	//renderer->renderStaticModel(glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f), camera, modelTest1, shaderPTNDepth0);
	//renderer->renderStaticModel(glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f), camera, modelTest2, shaderPTNDepth0);

	// FBOShadowMapping1->unbindFBOShadowMapping(); // After this process we have textureID (FBOShadowMapping1->getFBOShadowMapTextureID())
	// ----------------------------------------------------------------------------------------------------
	//
	// RENDER NORMAL CAM
	//
	waterFBO1->bindRefractionFrameBuffer(); // FBO 2 [ NORMAL RIGHT GUI] texID = 12
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);

	//renderer->renderSkyBox(camera, model_skyBox);
	//renderer->renderModelPTN(planeModelPTNBelow, camera, modelVanquish, shaderPTN1); // (y = -1)

	waterFBO1->unbindCurrentFrameBuffer();
	// =============================================
	// ----==== START RENDER IN MAIN SCREEN ====---- // RENDER order is IMPORTANT!
	// =============================================
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CLIP_DISTANCE0);

	renderer->renderSkyBox(camera, modelSkyBox00);
	//renderer->renderStaticModel(modelTest1, camera);
 //   renderer->renderStaticModel(modelTest2, camera);
	// =============================================
	// ----==== STOP RENDER IN MAIN SCREEN ====----
	// =============================================

	// RENDER IN GUIs
	modelGUI00->renderModel();  // FBO1 (texID = 8) TODO Hardcoded numbers
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

void RenderSceneMaster(std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>> _vectorOfSmartModelsPTN, GLfloat deltaTime);

int main(int argc, char** argv)
{
	system("Color 2"); // Set CMD color green
	// Init GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	// Give me screen resolution
	get_resolution();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3Ddev", nullptr, nullptr); // 4th parameter = glfwGetPrimaryMonitor() for fullscreen

	if (window == nullptr)
	{
		std::cout << "Error: Failed to create GLFW window" << std::endl;
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
	// IMPORTANT: OpenGL version after initialisation!
	std::cout << "|-------------------------------------------------" << std::endl;
	std::cout << "||  Starting GLFW context, OpenGL" << std::endl;
	std::cout << "||  Graphics vendor   : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "||  Renderer          : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "||  OpenGL version    : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "||  GLEW version      : " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "||  GLFW version      : " << glfwGetVersionString() << std::endl;
	std::cout << "||  Screen Resolution : " << WIDTH << " x " << HEIGHT << std::endl;
	std::cout << "|-------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::ofstream logFile("___Log/logFile.txt");
	//
	// ---- CREATE COMMON FUNCTIONs OBJECT ----
	//
	CommonFunctions* CF = new CommonFunctions(logFile);
	//
	// ----==== SHADERs [ ProjectionMatrix ] Initialization (only once) ====----
	//
	std::vector<std::shared_ptr<Shaders::ShadersIf::ShadersIf>> vectorOfSmartShaders;

	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderLearningOpenGL0>(new Shaders::ShaderLearningOpenGL0(WIDTH, HEIGHT)));
	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderPTN0>(new Shaders::ShaderPTN0(WIDTH, HEIGHT)));
	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderPTN1>(new Shaders::ShaderPTN1(WIDTH, HEIGHT)));
	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderSkyBox0>(new Shaders::ShaderSkyBox0(WIDTH, HEIGHT)));
	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderNormalMapPTNT0>(new Shaders::ShaderNormalMapPTNT0(WIDTH, HEIGHT)));
	vectorOfSmartShaders.push_back(std::shared_ptr<Shaders::ShaderMarker0>(new Shaders::ShaderMarker0(WIDTH, HEIGHT)));
	//
	// ----==== CAMERAs [ ViewMatrix ] ====----
	//
	camera = new Camera::Camera(glm::vec3(375, 25, 420), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//
	// ----==== FBOs ====----	
	//
	waterFBO1 = new FBOs::WaterFBO();
	waterFBO2 = new FBOs::WaterFBO();
	//
	// ----==== MODELs [ ModelMatrix ] ====----	
	//
	std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>> vectorOfSmartModelsPTN;
	// for each model in db try to create model...
	std::shared_ptr<Models::ModelPTN0> modelSmartPTN(new Models::ModelPTN0(CF, "_src/_models/_vanquish/", vectorOfSmartShaders));
	// Check error
	if (CF->checkError()) // Error
	{
		std::cout << "ERROR: Can't instanciate object!" << std::endl;
		CF->clearError();
		// delete object
	}
	else
	{
		vectorOfSmartModelsPTN.push_back(modelSmartPTN);
	}
	CF->clearError();
	vectorOfSmartModelsPTN.push_back(std::shared_ptr<Models::ModelPTN0>(new Models::ModelPTN0(CF, "_src/_models/lightMarker/", vectorOfSmartShaders)));


	// vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/_vanquish/", vectorOfShaders));
	//vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/cubeNM/", vectorOfShaders));
	//vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/barrelNM/", vectorOfShaders));
	//vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/_dagger/", vectorOfShaders));
	//vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/arrow/", vectorOfShaders));
	// vectorOfModelsPTN.push_back(new Models::ModelPTN0(CF, "_src/_models/lightMarker/", vectorOfShaders));
	// vectorOfModelsPTN[0]->printINFO();
	// LEGACY TODO
	std::vector<Shaders::ShadersIf::ShadersIf*> vectorOfShaders;
	vectorOfShaders.push_back(new Shaders::ShaderSkyBox0(WIDTH, HEIGHT));
	modelSkyBox00 = new Models::ModelSkyBox0(vectorOfShaders[0], camera);
	shaderWaterTile00 = new Shaders::ShaderWaterTile0(VS_Water_Tile, FS_Water_Tile);
	modelWaterTile00 = new Models::ModelWaterTile0("_src/water/waterDUDV.png", shaderWaterTile00, camera, 8, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(14.0f));
	shaderGUI00 = new Shaders::ShaderGUI0(VS2, FS2);
	modelGUI00 = new Models::ModelGUI0("sword.png", shaderGUI00, 10, glm::vec3(-0.7f, 0.5f, 0.f), glm::vec3(0.5f));
	modelGUI01 = new Models::ModelGUI0("socuwan.png", shaderGUI00, 9, glm::vec3(0.7f, 0.5f, 0.0f), glm::vec3(0.3));
	shaderTerrain00 = new Shaders::ShaderTerrain0(WIDTH, HEIGHT); // TODO: remove shader
	modelTerrain00 = new Models::ModelTerrain0(CF, "_src/_models/_vanquish/", vectorOfShaders);
	//
	// ----==== RENDERERs ====----	
	//
	renderer = new Renderer::Renderer();
	//
	// ----==== CMD ====----
	//
	CommandPrompt::CommandPrompt* CP = new CommandPrompt::CommandPrompt(vectorOfSmartShaders, vectorOfSmartModelsPTN);
	//
	//
	//
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	//
	//
	// TODO: [ THRED I ] COMMAND PROMPT
	//
	//
	std::cout << std::endl;
	std::cout << " [ Type help to start ]" << std::endl;
	CP->cmd();
	//
	//
	// TODO: [ THRED II ] GAME LOOP
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
		// DO PROCESSING
		//
		//
		// RENDER SCENE
		//
		// RenderScene(deltaTime);
		RenderSceneMaster(vectorOfSmartModelsPTN, deltaTime);
		//
		//
		//
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void RenderSceneMaster(std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>> _vectorOfSmartModelsPTN, GLfloat deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	// glEnable(GL_CLIP_DISTANCE0);

	// RENDER SKY BOX
	renderer->renderSkyBox(camera, modelSkyBox00);
	// RENDER TERRAIN
	renderer->renderTerrain(shaderTerrain00, modelTerrain00, camera);
	// RENDER MODELSPTN
	for (auto& it : _vectorOfSmartModelsPTN)
	{
		renderer->renderStaticModel(it, camera);
	}
	// TEST: Render another light in scene
	// Set new position
	//_vectorOfModelsPTN[2]->setModelPosition(glm::vec3(385, 50, 435)); // PTN LIGHT
	//renderer->renderStaticModel(_vectorOfModelsPTN[2], camera);
	// Reset on original position
	//_vectorOfModelsPTN[2]->setModelPosition(glm::vec3(380, 10, 380)); // TERRAIN LIGHT
}
