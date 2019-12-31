#pragma once

#include <string>

struct StringToken
{
	const std::string token;
	const std::string replacement;

	StringToken(std::string tokenArg, std::string replacementArg);
};

//Replaces tokens in string with other strings
std::string ReplaceStringTokens(const std::string& str, std::initializer_list<StringToken> tokens);

//Take only the filename from a path
std::string GetNameFromPath(const std::string& path);

//Remove any number of a particular character from the end of a string
std::string RemoveTrailingCharacters(const std::string& str, char character);

//Remove any number of a particular character from the beginning of a string
std::string RemovePrecedingCharacters(const std::string& str, char character);