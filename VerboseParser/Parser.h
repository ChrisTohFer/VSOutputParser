#pragma once

#include "VerboseParserTypes.h"
#include "VerboseOutputParser.h"

//This file provides the main interface for the parser

namespace VERBOSE
{
	struct LOG_KEY
	{
		int index;
		std::wstring path;
		std::wstring name();
	};

	std::vector<LOG_CONTENT>& storage();

	void add_to_storage(LOG_CONTENT log);
	void add_to_storage(std::vector<LOG_CONTENT> logs);
	void parse_and_add(const std::wstring&);
	void parse_and_add(const std::vector<std::wstring>&);

	std::vector<LOG_KEY> log_files();
}