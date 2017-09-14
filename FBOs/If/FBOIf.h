#ifndef FBOIF__
#define FBOIF__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
//
// GLEW
//
#include "../../__libs/glew-1.13.0/include/GL/glew.h"

namespace FBOs
{
namespace FBOIf
{
class FBOIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	//
	virtual ~FBOIf()
	{
		std::cout << "FBOIf destructor called!" << std::endl;
	}
	//
	// FUNCTIONs
	//
	virtual void bindReflectionFrameBuffer() {}
	virtual void bindRefractionFrameBuffer() {}
	virtual void unbindCurrentFrameBuffer() {}
	virtual int getReflectionTexture() { return 0;  }
	virtual int getRefractionTexture() { return 0; }
	virtual int getRefractionDepthTexture() { return 0; }
	virtual void initialiseReflectionFrameBuffer() {}
	virtual void initialiseRefractionFrameBuffer() {}
	virtual void bindFrameBuffer(int frameBuffer, int width, int height) {}
	virtual int createFrameBuffer() { return 0; }
	int createTextureAttachment(int width, int height) { return 0; }
	int createDepthTextureAttachment(int width, int height) { return 0; }
	int createDepthBufferAttachment(int width, int height) { return 0; }
	//
	// OPERATORs
	//			
	private:
	};
}
}

#endif