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