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

VERBOSE::LIBRARY& VERBOSE::PROJECT::library(int i)
{
	return libraries[i];
}

VERBOSE::LIBRARY& VERBOSE::PROJECT::library(std::string libpath)
{
	return libraries[libraryMap[libpath]];
}