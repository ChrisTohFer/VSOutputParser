#pragma once

#include <string>

//Replaces tokens in string with other strings
std::string ReplaceStringTokens(const std::string& str, std::initializer_list<std::pair<std::string, std::string>> tokens);

//Take only the filename from a path
std::string GetNameFromPath(const std::string& path);

//Remove any number of a particular character from the end of a string
std::string RemoveTrailingCharacters(const std::string& str, char character);

//Remove any number of a particular character from the beginning of a string
std::string RemovePrecedingCharacters(const std::string& str, char character);