#pragma once

namespace CommandPrompt
{
class CommandPrompt
{
	public:
	// CONSTRUCTORs / DESTRUCTORs
	CommandPrompt(std::vector<Shaders::ShadersIf::ShadersIf*> _vectorOfShaders,
		                      std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>> _vectorOfModels)
	{
		vectorOfShaders = _vectorOfShaders;
		vectorOfModels = _vectorOfModels;

		std::cout << "CommandPrompt created!" << std::endl;
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
			std::regex shadersCmd0("(\\w+)");
			if (std::regex_search(commandLineString, match, shadersCmd0))
			{
				if (!match.str(0).compare("shaders"))
				{
					std::cout << " shaders <names | <shader name> | all>" << std::endl;
				}
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

			// ----==============----
			// ----==== MODELS ====----
			// models
			std::regex modlelsCmd0("(\\w+)");
			if (std::regex_search(commandLineString, match, modlelsCmd0))
			{
				if (!match.str(0).compare("models"))
				{
					std::cout << " models <names | <model name> | all>" << std::endl;
				}
			}
			// models names
			std::regex modlelsCmd1("models\\s+names");
			if (std::regex_search(commandLineString, match, modlelsCmd1))
			{
				cmdModelsNames();
			}
			// model name
			std::regex modlelsCmd2("models\\s+(\\w+)");
			if (std::regex_search(commandLineString, match, modlelsCmd2))
			{
				cmdModelName(match.str(1));
			}
			// models all
			std::regex modlelsCmd3("models\\s+all");
			if (std::regex_search(commandLineString, match, modlelsCmd3))
			{
				cmdModelsAll();
			}
			// ----=================----

			// ----==============----
			// ----==== READ ====----
			// read
			std::regex readCmd0("(\\w+)");
			if (std::regex_search(commandLineString, match, readCmd0))
			{
				if (!match.str(0).compare("read"))
				{
					std::cout << " read <log | dataBase>" << std::endl;
				}
			}
			// read log
			std::regex readCmd1("read\\s+log");
			if (std::regex_search(commandLineString, match, readCmd1))
			{
				cmdReadLog();
			}
			// read database
			std::regex readCmd2("read\\s+dataBase");
			if (std::regex_search(commandLineString, match, readCmd2))
			{
				cmdReadDB();
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
		std::cout << " shaders   Info about Shaders and Shader Parameters" << std::endl;
		std::cout << " models    Info about Models, Meshes and Textures in scene" << std::endl;
		std::cout << " read      Read from File" << std::endl;
		std::cout << "" << std::endl;
		std::cout << " ---------------------" << std::endl;
	}
	// SHADERS
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
	// MODELS
	void cmdModelsNames()
	{
		std::cout << std::endl << " | Model Names: " << std::endl;
		std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>>::iterator it;
		for (it = vectorOfModels.begin(); it != vectorOfModels.end(); it++)
		{
			std::cout << "    " << (*it)->getModelName() << std::endl;
		}
	}

	void cmdModelName(std::string str)
	{
		std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>>::iterator it;
		for (it = vectorOfModels.begin(); it != vectorOfModels.end(); it++)
		{
			if (!str.compare((*it)->getModelName()))
			{
				(*it)->printINFO();
			}
		}
	}

	void cmdModelsAll()
	{
		std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>>::iterator it;
		for (it = vectorOfModels.begin(); it != vectorOfModels.end(); it++)
		{
			(*it)->printINFO();
		}
	}
	// READ
	void cmdReadLog()
	{
		std::ifstream logFile("___Log/logFile.txt");
		std::string logLine;
		while (std::getline(logFile, logLine))
		{
			std::cout << logLine << std::endl;
		}
	}

	void cmdReadDB()
	{
		std::ifstream dBFile("___Db/DataBase.txt");
		std::string dBLine;
		while (std::getline(dBFile, dBLine))
		{
			std::cout << dBLine << std::endl;
		}
	}
private:
	std::vector<Shaders::ShadersIf::ShadersIf*> vectorOfShaders;
	std::vector<std::shared_ptr<Models::ModelsIf::ModelsIf>> vectorOfModels;
};

}