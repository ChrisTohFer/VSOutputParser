#pragma once

#include <string>
#include <vector>

#include "VerboseParserTypes.h"

namespace VERBOSE {
	
	//parse an opened build log file and return an object with all the library information from that object
	LOG_CONTENT ParseLogFile(const std::string& path);
	std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::string>& paths);

}