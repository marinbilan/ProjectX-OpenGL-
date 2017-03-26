//
// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
// GLEW
#include "__libs\glew-1.13.0\include\GL\glew.h"
// GLFW
#include "__libs\glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h"
// GLM
#include "__libs\glm\glm\glm.hpp"
#include "__libs\glm\glm\gtc\matrix_transform.hpp"

// FREEIMAGE
#include "__libs\FreeImage\include\FreeImage.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
// Shaders Database [ Db ]
//
#include "Db\ShadersDb\shaderDb_PNT.h"
#include "Db\ShadersDb\shaderDb_Water.h"

#include "Db\ShadersDb\shaderDb_7.h"
#include "Db\ShadersDb\shaderDb_1.h"
#include "Db\ShadersDb\shaderDb_2.h" 
#include "Db\ShadersDb\shaderDb_3.h" 
//
// Shaders [ Projection ]
//
#include "Shaders\if\ShaderIf.h"

#include "Shaders\inc\Shader_PNT.h" // VANQUISH ASSIMP PNT  < pos, norms, texCords >
                                    // VERTEX SHADER        | proj, view, viewInv, transform, lightPos |
                                    // FRAGMENT SHADER      | modelTexture, lightColour, shineDamper, reflectivity |
#include "Shaders\inc\Shader_Water.h"

#include "Shaders\inc\Shader_7.h"   // ASSIMP and NORMAL MAPPING
#include "Shaders\inc\Shader_1.h"   // MODEL         PN  [ PROJECTION ]    <pos, norms | proj, view, model | light, normsRot>
#include "Shaders\inc\Shader_2.h"   // GUI           P   [ NO PROJECTION ] <pos | model >
#include "Shaders\inc\Shader_3.h"   // SKYBOX        P   [ PROJECTION ]    <pos | proj, view >
//
// Camera [ View ]
//
#include "Camera\if\CameraIf.h"

#include "Camera\inc\Camera.h"
//
// Models [ Model ]
//
#include "Models\if\ModelIf.h"

#include "Models\inc\Model_1.h"
#include "Models\inc\Model_GUI.h"
#include "Models\inc\Model_skyBox.h"
#include "Models\inc\Model_6.h"
#include "Models\inc\Mesh_1.h"
#include "Models\inc\Model_Assimp.h"
#include "Models\inc\Model_AssimpNormalMap.h"
//
// ASIMP TEST
//
// #include "Assimp\Mesh.h"
//
// LIGHT
//
GLfloat light1[] = { 0.0f, 15.0f, 15.0f, 1.0f };
GLfloat light2[] = { 0.0f, 15.0f, 15.0f};
//
//
// Shaders [ Projection ]
//
//
Shaders::Shader_PNT* shader_PNT_1;   // WITHOUT NORMAL MAP
Shaders::Shader_Water* shader_Water;

Shaders::Shader_7* shader_7; // WITH NORMAL MAP
Shaders::Shader_1* shader_1; // DRAGON
Shaders::Shader_2* shader_2; // GUI
Shaders::Shader_3* shader_3; // SKYBOX
//
// Camera [ View ]
//
Camera::Camera* camera;
//
// Models
//
Models::Model_Assimp*          modelAssimpTest1;
Models::Model_AssimpNormalMap* meshNM;

Models::Model_1*      model_1; // DRAGON
Models::Model_GUI*    model_GUI;
Models::Model_skyBox* model_skyBox;
Models::Model_Assimp* mesh_Assimp;
Models::Model_6*      model_6;
Models::Mesh_1*       mesh_1;
//
// Variables and Constants
//
GLuint WIDTH;
GLuint HEIGHT;

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

#include "Controls\Contorls.h"

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	// ----==== RENDER SKYBOX ====----
	//
	model_skyBox->renderModel();
	//
	// LIGHT params
	//
	GLfloat lightPosition[] = { 0.0f, 35.0f, 35.0f };
	GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };
	GLfloat shineDamper = 15.0f;
	GLfloat reflectivity = 1.6f;
	//
	// UPDATE GAME STATE
	//
	// Update CAMERA
	camera->updateCameraPosition();
	//
	// PREPARE MODEL
	//
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, -1.55f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, (WIDTH / HEIGHT)));
	//
	// #### START SHADER ####
	//
	glUseProgram(shader_PNT_1->getShaderProgramID());

	// UPDATE PROJECTION MATRIX only once in shader constructor
	// UPDATE VIEW MATRIX
	// UPDATE INVVIEW MATRIX
	camera->updateCameraUniform(shader_PNT_1);
	// UPDATE MODEL MATRIX
	glUniformMatrix4fv(shader_PNT_1->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform3f(shader_PNT_1->getLightID(), lightPosition[0], lightPosition[1], lightPosition[2]);
	// TO DO: Texture ids
	glUniform3f(shader_PNT_1->getlightColorID(), lightColour[0], lightColour[1], lightColour[2]);
	glUniform1f(shader_PNT_1->getshineDamperID(), shineDamper);
	glUniform1f(shader_PNT_1->getreflectivityID(), reflectivity);
	//
	// ----==== RENDER MODEL ====----
	//
	// VANQUISH MODEL RENDER (6 meshes)
	modelAssimpTest1->Render();
	//modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 15.0f));
	//modelMatrix = glm::rotate(modelMatrix, -1.55f, glm::vec3(1.0f, 0.0f, 0.0f));
	//mesh_Grass->Render();
	glBindVertexArray(0);
	glUseProgram(0);



	// mesh_1->renderModel();

	//
	// ----==== RENDER NORMAL MAP MODEL ====----
	//
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
	
	//model_GUI->renderModel();

	//
	// ----==== CLOCK ====----
	//
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
	//
	// Shaders [ Projection ] Initialization (only once)
	//
	//
	shader_PNT_1 = new Shaders::Shader_PNT(VS_PNT, FS_PNT);
	shader_Water = new Shaders::Shader_Water(VS_Water, FS_Water);

	shader_3 = new Shaders::Shader_3(VS3, FS3);
	shader_7 = new Shaders::Shader_7(VS7, FS7);
	shader_1 = new Shaders::Shader_1(VS1, FS1);
	shader_2 = new Shaders::Shader_2(VS2, FS2);
	//
	// Shaders Info
	//
	std::cout << *shader_PNT_1;
	std::cout << *shader_Water;

	std::cout << *shader_3;
	//std::cout << *shader_7;
	//std::cout << *shader_1;
	//std::cout << *shader_2;
	//
	//
	// Camera [ View ] Initialization
	//
	//
	//
	camera = new Camera::Camera();
	//
	//
	// Models [ Model ] Initialization
	//
	//
	modelAssimpTest1 = new Models::Model_Assimp("_src/_models/vanquish/", shader_PNT_1, camera, light1);
	model_skyBox = new Models::Model_skyBox(shader_3, camera);

	//meshNM = new Models::Model_AssimpNormalMap("_src/_models/barrel/", shader_7, camera, light1);
	// TO DO: clean variable names
	//model_1 = new Models::Model_1(shader_1, camera, light1);
	//model_GUI = new Models::Model_GUI(shader_2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
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
		RenderScene();
		//
		//
		//
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}