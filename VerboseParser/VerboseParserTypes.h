#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

namespace VERBOSE
{
	enum class LIB_TYPE
	{
		DLL,
		STATIC
	};

	//contains all the information parsed from a log file for a specific symbol
	struct SYMBOL
	{
		std::set<std::string> references;
	};

	//contains all the information parsed from a log file for a specific library
	struct LIBRARY
	{

		bool defaultLib = false;
		
		LIB_TYPE type = LIB_TYPE::STATIC;
		std::string name;
		std::string path;
		std::string parent = "No Name";
		std::map<std::string, SYMBOL> symbols;
		std::set<std::string> references;

		LIBRARY(std::string pathArg);
		bool IsUsed();
	};

	//contains information on a library collected from multiple projects/log files
	struct LIBRARY_SUMMARY
	{
		std::string name;
		std::string path;

		std::map<std::string, LIBRARY> references;
	};

	//contains all the information parsed from a log file for a specific project
	struct PROJECT
	{
		std::string name = "No Name";
		std::map<std::string, int> libraryMap;
		std::vector<LIBRARY> libraries;

		LIBRARY& library(int);
		LIBRARY& library(std::string);
	};

	//contains all the information parsed from a log file
	struct LOG_CONTENT
	{
		std::string path;
		std::wstring wpath;
		std::vector<PROJECT> projects;
	};

}