#ifndef COMMONFUNCTIONS__
#define COMMONFUNCTIONS__

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
// GLEW
#include "../../__libs/glew-1.13.0/include/GL/glew.h"
// GLFW
#include "..\..\__libs\glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h"
// GLM
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp" // For Projection Matrix in ShaderIf
// ASSIMP
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/Importer.hpp"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/postprocess.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/mesh.h"
#include "../../__libs/assimp--3.0.1270-sdk/include/assimp/scene.h"
// FREE IMAGE
#include "../../__libs/FreeImage/include/FreeImage.h"

// #define
#define LOG __DATE__, __TIME__, __FILENAME__, __LINE__,
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

class CommonFunctions
{
public:
	CommonFunctions(std::ofstream& _logFile) : logFile(_logFile)
	{
		std::cout << " CommonFunction and Log File created" << std::endl;
	};

	static void setFontColor(int color)
	{
	}

	void LOGFILE(const char* date, const char* time, const char* file, int line, std::string msg)
	{
		logFile << "[ " << date << " " << time << " ]" << " { FILENAME: " << file << " }" << " { LINE: " << line << " }" << " { INFO: " << msg << " }" << std::endl;
	}

	static void INFOCMD(const char* date, const char* time, const char* file, int line, std::string msg) // const char* msg
	{
		std::cout << "[ " << date << " " << time << " ]" << " { FILENAME: " << file << " }" << " { LINE: " << line << " }"<< " { INFO: " << msg << " }"<< std::endl;
	}

	static void getFromDB(std::string dbEntry, std::string dbTarget, std::string& dbParam)
	{		
		// dB File
		std::ifstream dBFile("___Db/DataBase.txt");
		// dB Line
		std::string dBLine;
		// db Regex
		std::regex regexLine(dbEntry + "\\s+" + dbTarget + "\\s+(\\w+)");
 
		std::smatch match;
		while (std::getline(dBFile, dBLine))
		{
			if (std::regex_search(dBLine, match, regexLine))
			{
				dbParam = match.str(1); // match.str(0) // Whole matched string
			}
			else {
				// std::cout << "No match!" << std::endl;
			}
		}		
	}

	static void getFromDB(std::string dbEntry, std::string dbTarget, GLfloat& dbParam)
	{
		// dB File
		std::ifstream dBFile("___Db/DataBase.txt");
		// dB Line
		std::string dBLine;
		// db Regex
		std::regex regexLine(dbEntry + "\\s+" + dbTarget + "\\s+([-]?\\d+)(\\.\\d+)?");

		std::smatch match;
		while (std::getline(dBFile, dBLine))
		{
			if (std::regex_search(dBLine, match, regexLine))
			{
				dbParam = std::stof(match.str(1) + match.str(2)); // match.str(0) // Whole matched string
			}
			else {
				// std::cout << "No match!" << std::endl;
			}
		}
	}

	static void getFromDB(std::string dbEntry, std::string dbTarget, glm::vec3& dbParam)
	{
		// dB File
		std::ifstream dBFile("___Db/DataBase.txt");
		// dB Line
		std::string dBLine;
		// dB Regex
		std::regex regexLine(dbEntry + "\\s+" + dbTarget + "\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?");

		std::smatch match;
		while (std::getline(dBFile, dBLine))
		{
			if (std::regex_search(dBLine, match, regexLine))
			{
				dbParam = glm::vec3( std::stof(match.str(1) + match.str(2)), 
					                 std::stof(match.str(3) + match.str(4)), 
					                 std::stof(match.str(5) + match.str(6)) );
			}
			else 
			{
				// std::cout << "No match!" << std::endl;
			}
		}
	}

private:
	std::ofstream& logFile;
};
#endif