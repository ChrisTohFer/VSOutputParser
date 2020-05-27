#pragma once

#include "VerboseParserTypes.h"
#include "VerboseOutputParser.h"

#include <vector>
#include <map>

//This file provides the main interface for the parser

namespace VERBOSE
{
	struct LOG_KEY
	{
		int index;
		std::wstring path;
		std::wstring name();

		LOG_CONTENT log();
	};
	struct PROJECT_KEY
	{
		int log_index;
		int proj_index;
		std::string name;

		PROJECT project();
	};
	struct LIBRARY_KEY
	{
		int log_index;
		int proj_index;
		int lib_index;
		std::string name;

		LIBRARY library();
	};

	std::vector<LOG_CONTENT>& storage();

	

	void add_to_storage(LOG_CONTENT log);
	void add_to_storage(std::vector<LOG_CONTENT> logs);
	void parse_and_add(const std::wstring&);
	void parse_and_add(const std::vector<std::wstring>&);

	std::vector<LOG_KEY> log_files();
	std::vector<PROJECT_KEY> projects(std::vector<LOG_KEY> logs);
	std::vector<LIBRARY> libraries(std::vector<PROJECT_KEY> projects);
}