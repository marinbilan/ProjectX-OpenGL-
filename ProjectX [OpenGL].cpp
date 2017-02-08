//
// GAMEDEV Framework Marin Bilan @2017
// cd "D:\Marin\__Programming\Projects\Programing\ProjectX [OpenGL]\ProjectX [OpenGL]"
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
// GLEW
#include "__libs\glew-1.13.0\include\GL\glew.h"
// GLFW
#include "__libs\glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h"
// GLM
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
// FREEIMAGE
#include "__libs\FreeImage\include\FreeImage.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
// Shader Database [ Db ]
//
#include "Db\ShadersDb\shaderDb_1.h"
#include "Db\ShadersDb\shaderDb_2.h" // GUI
#include "Db\ShadersDb\shaderDb_3.h" // SKYBOX
#include "Db\ShadersDb\shaderDb_4.h"
#include "Db\ShadersDb\shaderDb_5.h"
//
// Shaders [ Projection ]
//
#include "Shaders\if\ShaderIf.h"

#include "Shaders\inc\Shader_1.h" // MODEL         PN  [ PROJECTION ]    <pos, norms | proj, view, model | light, normsRot>
#include "Shaders\inc\Shader_2.h" // GUI           P   [ NO PROJECTION ] <pos | model >
#include "Shaders\inc\Shader_3.h" // SKYBOX        P   [ PROJECTION ]    <pos | proj, view >
#include "Shaders\inc\Shader_4.h" // THIN MATRIX   PNT [ PROJECTION ]   
#include "Shaders\inc\Shader_5.h" // TEXTURED CUBE PNT [ PROJECTION ]
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
#include "Models\inc\Model_NormalMap.h"
//
// LIGHT
//
GLfloat light1[] = { 0.0f, 5.0f, 5.0f, 1.0f };
//
//
// Shaders [ Projection ]
//
//
Shaders::Shader_1* shader_1; 
Shaders::Shader_2* shader_2; 
Shaders::Shader_3* shader_3; 
Shaders::Shader_4* shader_4; 
Shaders::Shader_5* shader_5;
//
// Camera [ View ]
//
Camera::Camera* camera;
//
// Models
//
Models::Model_1* model_1; // DRAGON
Models::Model_GUI* model_GUI;
Models::Model_skyBox* model_skyBox;
Models::Model_NormalMap* model_NormalMap;
//
// Variables and Constants
//
GLuint WIDTH = 1024;
GLuint HEIGHT = 768;

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

#include "Controls\Contorls.h"

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	// UPDATE GAME STATE
	//
	camera->updateCameraPosition();
	//
	// RENDER MODELs
	//
	model_skyBox->renderModel();
	model_1->renderModel();
	model_NormalMap->renderModel();
	model_GUI->renderModel();

	//std::clock_t start = std::clock();
	//double duration;

	//std::clock_t end = std::clock();
	//duration = (end - start) / (double)CLOCKS_PER_SEC;
	//std::cout << "Trajanje algoritma: " << duration << std::endl;
}

void get_resolution() {
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

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
	shader_1 = new Shaders::Shader_1(VS1, FS1);
	shader_2 = new Shaders::Shader_2(VS2, FS2);
	shader_3 = new Shaders::Shader_3(VS3, FS3);
	shader_4 = new Shaders::Shader_4(VS4, FS4);
	shader_5 = new Shaders::Shader_5(VS5, FS5);
	//
	// Shaders Info
	//
	std::cout << *shader_1;
	std::cout << *shader_2;
	std::cout << *shader_3;
	std::cout << *shader_4;
	std::cout << *shader_5;
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
	model_1 = new Models::Model_1(shader_1, camera, light1);
	model_GUI = new Models::Model_GUI(shader_2);
	model_skyBox = new Models::Model_skyBox(shader_3, camera);
	model_NormalMap = new Models::Model_NormalMap(shader_5, camera, light1);

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