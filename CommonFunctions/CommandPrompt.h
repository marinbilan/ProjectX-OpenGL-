#ifndef COMMANDPROMPT__
#define COMMANDPROMPT__

#include "..\..\Shaders\if\ShaderIf.h"

namespace CommandPrompt
{
class CommandPrompt
{
	public:
	// CONSTRUCTORs / DESTRUCTORs
	CommandPrompt(std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders,
		          std::vector<Models::ModelsIf::ModelsIf*> _vectorOfModels)
	{
		vectorOfShaders = _vectorOfShaders;
		vectorOfModels = _vectorOfModels;
	}
	~CommandPrompt()
	{
		std::cout << "CommandPrompt destructor called!" << std::endl;
	}
	// COMMAND PROMPT
	// MASTER cmd
	void cmd()
	{
		std::string commandLineString;
		std::smatch match;
		do
		{
			std::cout << "> ";
			std::getline(std::cin, commandLineString);

			// ----==== HELP ====----
			std::regex helpCmd("help");
			if (std::regex_search(commandLineString, match, helpCmd))
			{
				cmdHelp();
			}
			// ----==============----
			// ----==== SAHDERS ====----
			// shaders
			std::regex shadersCmd0("shaders");
			if (std::regex_search(commandLineString, match, shadersCmd0))
			{
				std::cout << " shaders <names | < shader name > | all>" << std::endl;
			}
			// shaders names
			std::regex shadersCmd1("shaders\\s+names");
			if (std::regex_search(commandLineString, match, shadersCmd1))
			{
				cmdShadersNames();
			}
			// shaders all
			std::regex shadersCmd2("shaders\\s+all");
			if (std::regex_search(commandLineString, match, shadersCmd2))
			{
				cmdShadersAll();
			}
			// ----=================----
		} while (commandLineString != "exit");
	}

	void cmdHelp()
	{
		std::cout << "" << std::endl;
		std::cout << " ----==== HELP ====---- " << std::endl;
		std::cout << "" << std::endl;
		std::cout << " cameras   Info about cameras In scene " << std::endl;
		std::cout << " controls  Info about controls (Keys)" << std::endl;
		std::cout << " fbos      Info about generated Frame Buffer Objects" << std::endl;
		std::cout << " models    Info about Models, Meshes and Textures in scene" << std::endl;
		std::cout << " shaders   Info about Shaders and Shader Parameters" << std::endl;
		std::cout << " logread   Show log" << std::endl;
		std::cout << "" << std::endl;
		std::cout << " ---------------------" << std::endl;
	}

	void cmdShadersNames()
	{
		std::cout << std::endl << " | Shader Names: " << std::endl;
		std::vector<Shaders::ShadersIf::ShadersIf*>::iterator it;
		for (it = vectorOfShaders.begin(); it != vectorOfShaders.end(); it++)
		{
			std::cout << "    " << (*it)->getShaderName() << std::endl;
		}
	}

	void cmdShadersAll()
	{
		std::vector<Shaders::ShadersIf::ShadersIf*>::iterator it;
		for (it = vectorOfShaders.begin(); it != vectorOfShaders.end(); it++)
		{
			(*it)->printINFO();
		}
	}

	void cmdModelsNames()
	{
		std::vector<Models::ModelsIf::ModelsIf*>::iterator it;
		for (it = vectorOfModels.begin(); it != vectorOfModels.end(); it++)
		{
			std::cout << (*it)->getModelName() << std::endl;
		}
	}

private:
	std::vector<Shaders::ShadersIf::ShadersIf*> vectorOfShaders;
	std::vector<Models::ModelsIf::ModelsIf*> vectorOfModels;
};

}
#endif