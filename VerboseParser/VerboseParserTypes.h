#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

namespace VERBOSE
{

	//contains all the information parsed from a log file for a specific symbol
	struct SYMBOL
	{
		std::set<std::string> references;
	};

	//contains all the information parsed from a log file for a specific library
	struct LIBRARY
	{
		enum class TYPE
		{
			DLL,
			STATIC
		};

		bool defaultLib = false;
		
		TYPE type = TYPE::STATIC;
		std::string name;
		std::string path;
		std::map<std::string, SYMBOL> symbols;
		std::set<std::string> references;

		LIBRARY(std::string pathArg);
		bool IsUsed();
	};

	//contains all the information parsed from a log file
	struct LOG_CONTENT
	{
		std::map<std::string, int> libraryMap;
		std::vector<LIBRARY> libraries;

		LIBRARY& library(int);
		LIBRARY& library(std::string);
	};

}