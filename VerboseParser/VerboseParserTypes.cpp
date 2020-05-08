#include "VerboseParserTypes.h"
#include "GenericFunctions/StringFunctions.h"

VERBOSE::LIBRARY::LIBRARY(std::string pathArg)
	: path(pathArg)
	, name(GetNameFromPath(pathArg))
{}
bool VERBOSE::LIBRARY::IsUsed()
{
	return symbols.size() != 0;
}

VERBOSE::LIBRARY& VERBOSE::LOG_CONTENT::library(int i)
{
	return libraries[i];
}

VERBOSE::LIBRARY& VERBOSE::LOG_CONTENT::library(std::string path)
{
	return libraries[libraryMap[path]];
}