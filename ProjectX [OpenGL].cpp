// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"

#include "Db\IncludesDb\includesDb.h"
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
//                                           +------------------+                                           |                     |
//                                           | ProjectX [OpenGL]| <-----------------------------------------+---------------------+
//						                     +------------------+
//
// Shaders [ Projection ]
Shaders::ShaderSkyBox0*         shaderSkyBox00;            // SKYBOX
Shaders::ShaderWaterTile0*      shaderWaterTile00;         // WATER
Shaders::ShaderLearningOpenGL0* shaderLearningOpenGL00;
Shaders::ShaderPTN0*            shaderPTN00;               
Shaders::ShaderGUI0*            shaderGUI00;               // GUI

// Camera [ View ]
Camera::Camera* camera;

// FBOs
FBOs::WaterFBO* waterFBO1;
FBOs::WaterFBO* waterFBO2;

// Models [ Model ]
Models::ModelSkyBox0*     modelSkyBox00;
Models::ModelWaterTile0*  modelWaterTile00;
Models::ModelPTN0*        modelTest1;
Models::ModelPTN0*        modelTest2;
Models::ModelGUI0*        modelGUI00;
Models::ModelGUI0*        modelGUI01;

// Renderers
Renderer::Renderer* renderer;

// Variables and Constants
GLuint WIDTH;
GLuint HEIGHT;

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

#include "Controls\Contorls.h"
// GLfloat planeModelPTN[] = { 0.0f, -1.0f, 0.0f, 100000.0f };    // HACK (glDisable doesn't work!)

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
	renderer->renderStaticModel(modelTest1, camera);
    renderer->renderStaticModel(modelTest2, camera);
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

void RenderSceneMaster(GLfloat deltaTime);

int main(int argc, char** argv)
{
	system("Color 2"); // Set CMD color green
    // ---- SETUP LOG FILE ----
	std::ofstream logFile("___Log/logFile.txt");
	// ---- CREATE COMMON FUNCTIONs OBJECT ----
	CommonFunctions* CF = new CommonFunctions(logFile);
	CF->LOGFILE(LOG "My First msg from MAIN");

	std::cout << "+---------------------------------+" << std::endl;
	std::cout << "|  Starting GLFW context, OpenGL  |" << std::endl;
	std::cout << "+---------------------------------+" << std::endl;

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
	//
	// ----==== SHADERs [ ProjectionMatrix ] Initialization (only once) ====----
	//
	shaderSkyBox00 = new Shaders::ShaderSkyBox0(VS3, FS3);
	shaderWaterTile00 = new Shaders::ShaderWaterTile0(VS_Water_Tile, FS_Water_Tile);
	shaderLearningOpenGL00 = new Shaders::ShaderLearningOpenGL0(VSLearningOpenGL0, FSLearningOpenGL0);
	shaderPTN00 = new Shaders::ShaderPTN0(VSPTN, FSPTN);
	shaderGUI00 = new Shaders::ShaderGUI0(VS2, FS2);
	// Shader Container
	std::vector<Shaders::ShadersIf::ShadersIf*> vectorOfShaders;
	std::vector<Shaders::ShadersIf::ShadersIf*>::iterator it;

	vectorOfShaders.push_back(shaderLearningOpenGL00);
	vectorOfShaders.push_back(shaderPTN00);

	//for (it = vectorOfShaders.begin(); it != vectorOfShaders.end(); it++)
	//{
	//	std::cout << (*it)->getShaderName().compare("ShaderPTN0") << std::endl;
	//	(*it)->printINFO();
	//}

	// Shaders INFO
	// std::cout << *shaderLearningOpenGL00;
	std::cout << "SHADER ADDRESS: " << shaderPTN00;
	//
	// ----==== CAMERAs [ ViewMatrix ] ====----
	//
	camera = new Camera::Camera(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Current Light position
	//
	// ----==== FBOs ====----	
	//
	waterFBO1 = new FBOs::WaterFBO();
	waterFBO2 = new FBOs::WaterFBO();
	//
	// ----==== MODELs [ ModelMatrix ] ====----	
	//
	modelSkyBox00 = new Models::ModelSkyBox0(shaderSkyBox00, camera);
	modelTest1 = new Models::ModelPTN0(CF, "_src/_models/_vanquish/", vectorOfShaders);
	modelTest2 = new Models::ModelPTN0(CF, "_src/_models/_dagger/", vectorOfShaders);
	modelWaterTile00 = new Models::ModelWaterTile0("_src/water/waterDUDV.png", shaderWaterTile00, camera, 8, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(14.0f));
	modelGUI00 = new Models::ModelGUI0("sword.png", shaderGUI00, 10, glm::vec3(-0.7f, 0.5f, 0.f), glm::vec3(0.5f));
	modelGUI01 = new Models::ModelGUI0("socuwan.png", shaderGUI00, 9, glm::vec3(0.7f, 0.5f, 0.0f), glm::vec3(0.3));
	// Models INFO
	std::cout << *modelTest1;
	std::cout << *modelTest2;
	//
	// ----==== RENDERERs ====----	
	//
	renderer = new Renderer::Renderer();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	std::string commandLineString;
	std::smatch match;
	do 
	{
		std::cout << "> ";
		std::getline(std::cin, commandLineString);

		std::regex helpCmd("help");
		std::regex shadersCmd("Shaders");

		if (std::regex_search(commandLineString, match, helpCmd))
		{
			std::cout << "" << std::endl;
			std::cout << " ----==== HELP ====---- " << std::endl;
			std::cout << "" << std::endl;
			std::cout << " Cameras   Info about cameras In scene " << std::endl;
			std::cout << " Controls  Info about controls (Keys)" << std::endl;
			std::cout << " FBOs      Info about generated Frame Buffer Objects" << std::endl;
			std::cout << " Models    Info about Models, Meshes and Textures in scene" << std::endl;
			std::cout << " Shaders   Info about Shaders and Shader Parameters" << std::endl;
			std::cout << " logread   Show log" << std::endl;
			std::cout << "" << std::endl;
			std::cout << " ---------------------" << std::endl;
		}
		if (std::regex_search(commandLineString, match, shadersCmd))
		{
			for (it = vectorOfShaders.begin(); it != vectorOfShaders.end(); it++)
			{
				(*it)->printINFO();
			}
		}
	} while (commandLineString != "exit");
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
		// DO PROCESSING
		//
		//
		// RENDER SCENE
		//
		// RenderScene(deltaTime);
		RenderSceneMaster(deltaTime);
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
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	// glEnable(GL_CLIP_DISTANCE0);

	renderer->renderSkyBox(camera, modelSkyBox00);
	renderer->renderStaticModel(modelTest1, camera);
	renderer->renderStaticModel(modelTest2, camera);
}