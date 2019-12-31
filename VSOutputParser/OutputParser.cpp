#include "VerboseParser/VerboseOutputParser.h"
#include "GenericFunctions/StringFunctions.h"

int main()
{
	std::string path("C:/temp/<C>/WindowsPractise.log");
	std::string configs[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", };
	std::vector<std::string> paths;
	std::vector<VERBOSE::LOG_CONTENT> logs;

	for (size_t i = 0; i < 12; ++i)
	{
		paths.push_back(ReplaceStringTokens(path, { StringToken("<C>", configs[i]) }));
	}

	logs = VERBOSE::ParseLogFiles(paths);

	return 0;
}