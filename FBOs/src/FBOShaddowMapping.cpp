#include "../inc/FBOShaddowMapping.h"

// CONSTRUCTORs / DESTRUCTOR(s)
FBOs::FBOShaddowMapping::FBOShaddowMapping(int _shadowWidth, int _shadowHeight, int _screenWidth, int _screenHeight) :
	                     shadowWidth(_shadowWidth), shadowHeight(_shadowHeight), screenWidth(_screenWidth), screenHeight(_screenHeight)
{
	createFBOShadowMapping();
}
// DESTRUCTOR
FBOs::FBOShaddowMapping::~FBOShaddowMapping()
{
}
// FUNCTIONs
void FBOs::FBOShaddowMapping::createFBOShadowMapping()
{
	// Frame Buffer 
	glGenFramebuffers(1, &FBOShadowMapID);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOShadowMapID);
	// Texture
	glGenTextures(1, &FBOShadowMapTextureID);
	glBindTexture(GL_TEXTURE_2D, FBOShadowMapTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Frame Buffer and Texture are created and binded (Connect FBO with current texture)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, FBOShadowMapTextureID, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind buffer
}

void FBOs::FBOShaddowMapping::bindFBOShadowMapping()
{
	glBindTexture(GL_TEXTURE_2D, 0); //To make sure the another texture isn't bound
	glViewport(0, 0, shadowWidth, shadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOShadowMapID);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void FBOs::FBOShaddowMapping::unbindFBOShadowMapping()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint FBOs::FBOShaddowMapping::getFBOShadowMapID()
{
	return FBOShadowMapID;
}

GLuint FBOs::FBOShaddowMapping::getFBOShadowMapTextureID()
{
	return FBOShadowMapTextureID;
}

