#pragma once

#include <string>
#include <vector>

#include "VerboseParserTypes.h"

namespace VERBOSE {
	
	//parse a file and return an object with all the library information from that file
	LOG_CONTENT ParseLogFile(const std::string& path);

	//parse multiple files and return a vector of objects containing the library information from those files
	std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::string>& paths);

}