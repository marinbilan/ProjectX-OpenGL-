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
	//
	// OPERATORs
	//			
	private:
	};
}
}

#endif