#include "../inc/WaterFBO.h"

// CONSTRUCTORs / DESTRUCTOR(s)
FBOs::WaterFBO::WaterFBO()
{
	REFLECTION_WIDTH = 320;
	REFLECTION_HEIGHT = 180;

	REFRACTION_WIDTH = 320;
	REFRACTION_HEIGHT = 180;

	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
	// initShaddowMapFBO();
	std::cout << "WaterFBO created!" << std::endl;
}

FBOs::WaterFBO::~WaterFBO()
{
}
//void cleanUp() { //call when closing the game
//	glDeleteFramebuffers(reflectionFrameBuffer);
//	glDeleteTextures(reflectionTexture);
//	glDeleteRenderbuffers(reflectionDepthBuffer);
//	glDeleteFramebuffers(refractionFrameBuffer);
//	glDeleteTextures(refractionTexture);
//	glDeleteTextures(refractionDepthTexture);
//}

void FBOs::WaterFBO::bindReflectionFrameBuffer() { //call before rendering to this FBO
	bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void FBOs::WaterFBO::bindRefractionFrameBuffer() { //call before rendering to this FBO
	bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void FBOs::WaterFBO::unbindCurrentFrameBuffer() {//call to switch to default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1366.0f, 768.0f);
}

int FBOs::WaterFBO::getReflectionTexture() {//get the resulting texture
	return reflectionTexture;
}

int FBOs::WaterFBO::getRefractionTexture() {//get the resulting texture
	return refractionTexture;
}

int FBOs::WaterFBO::getRefractionDepthTexture() {//get the resulting depth texture
	return refractionDepthTexture;
}

void FBOs::WaterFBO::initialiseReflectionFrameBuffer() {
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void FBOs::WaterFBO::initialiseRefractionFrameBuffer() {
	refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void FBOs::WaterFBO::bindFrameBuffer(int frameBuffer, int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0); //To make sure the another texture isn't bound
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

// 1
int FBOs::WaterFBO::createFrameBuffer() {

	GLuint frameBuffer;

	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0); // Doesn t need this

	return frameBuffer;
}
// 2
int FBOs::WaterFBO::createTextureAttachment(int width, int height) {

	GLuint texture;
	glGenTextures(1, &texture);
	// std::cout << ">>> texture: " << texture << std::endl;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	// ALTERNATIVNO: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0); // Access VIOLATION!
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	return texture;
}

int FBOs::WaterFBO::createDepthTextureAttachment(int width, int height) {

	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0); // Access VIOLATION!
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	return texture;
}
// 3
int FBOs::WaterFBO::createDepthBufferAttachment(int width, int height) {

	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);

	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	return depthBuffer;
}

//
// TESTING DODATNO
//
void FBOs::WaterFBO::initShaddowMapFBO()
{
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	unsigned int depthMap;
	glGenTextures(1, &depthMap);

	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
	SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	// Create new function for this
	//
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::cout << ">>> depthMapFBO (Buffer): " << depthMapFBO << std::endl;
	std::cout << ">>> depthMap (Texture): " << depthMapFBO << std::endl;
}
