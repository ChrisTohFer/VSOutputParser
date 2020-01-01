#pragma once

#include <string>
#include <vector>

#include "VerboseParserTypes.h"

namespace VERBOSE {

	//functions are templated to accept both std::string and std::wstring

	//parse a file and return an object with all the library information from that file
	template<typename CHAR_TYPE>
	LOG_CONTENT ParseLogFile(const std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>& path);

	//parse multiple files and return a vector of objects containing the library information from those files
	template<typename CHAR_TYPE>
	std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>>& paths);

}