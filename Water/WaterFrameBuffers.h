#include "../__libs/glew-1.13.0/include/GL/glew.h"

class WaterFrameBuffers {
public:
	int REFLECTION_WIDTH = 320;
	int REFLECTION_HEIGHT = 180;

	//int REFRACTION_WIDTH = 1280;
	//int REFRACTION_HEIGHT = 720;
	int REFRACTION_WIDTH = 320;
	int REFRACTION_HEIGHT = 180;

	int reflectionFrameBuffer;
	int reflectionTexture;
	int reflectionDepthBuffer;

	int refractionFrameBuffer;
	int refractionTexture;
	int refractionDepthTexture;

	WaterFrameBuffers() { //call when loading the game

		initialiseReflectionFrameBuffer();
		initialiseRefractionFrameBuffer();
	}

	//void cleanUp() { //call when closing the game
	//	glDeleteFramebuffers(reflectionFrameBuffer);
	//	glDeleteTextures(reflectionTexture);
	//	glDeleteRenderbuffers(reflectionDepthBuffer);
	//	glDeleteFramebuffers(refractionFrameBuffer);
	//	glDeleteTextures(refractionTexture);
	//	glDeleteTextures(refractionDepthTexture);
	//}

	void bindReflectionFrameBuffer() { //call before rendering to this FBO
		bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	void bindRefractionFrameBuffer() { //call before rendering to this FBO
		bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	void unbindCurrentFrameBuffer() {//call to switch to default frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1366.0f, 768.0f);
	}

	int getReflectionTexture() {//get the resulting texture
		return reflectionTexture;
	}

	int getRefractionTexture() {//get the resulting texture
		return refractionTexture;
	}

	int getRefractionDepthTexture() {//get the resulting depth texture
		return refractionDepthTexture;
	}

	void initialiseReflectionFrameBuffer() {
		reflectionFrameBuffer = createFrameBuffer();
		reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		unbindCurrentFrameBuffer();
	}

	void initialiseRefractionFrameBuffer() {
		refractionFrameBuffer = createFrameBuffer();
		refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		unbindCurrentFrameBuffer();
	}

	void bindFrameBuffer(int frameBuffer, int width, int height) {
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, width, height);
	}

	int createFrameBuffer() {

		GLuint frameBuffer;

		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		return frameBuffer;
	}

	int createTextureAttachment(int width, int height) {

		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		// ALTERNATIVNO: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0); // Access VIOLATION!
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		return texture;
	}

	int createDepthTextureAttachment(int width, int height) {

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

	int createDepthBufferAttachment(int width, int height) {

		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);

		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

		return depthBuffer;
	}
};