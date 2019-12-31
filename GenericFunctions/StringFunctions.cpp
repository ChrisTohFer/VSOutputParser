#include "StringFunctions.h"
#include <string>

std::string ReplaceStringTokens(const std::string& str, std::initializer_list<std::pair<std::string, std::string>> tokens)
{
	std::string output = str;

	//for each token type, find and replace until none are left
	for (size_t i = 0u; i < tokens.size(); ++i)
	{
		bool tokensRemain = true;
		while (tokensRemain)
		{
			const auto& pair = *(tokens.begin() + i);
			const auto& token = pair.first;

			auto tokenStart = output.find(token);
			if (tokenStart == std::string::npos)
			{
				tokensRemain = false;
			}
			else
			{
				output.replace(tokenStart, token.size(), pair.second);
			}
		}
	}

	return output;
}

std::string GetNameFromPath(const std::string& path)
{
	//Find the last backslash or slash in the path
	size_t newFirstCharacter = 0u;

	auto slash = path.find_last_of('/');
	if (slash != std::string::npos)
		newFirstCharacter = slash + 1u;

	auto backslash = path.find_last_of('\\');
	if (backslash != std::string::npos && backslash >= newFirstCharacter)
		newFirstCharacter = backslash + 1u;

	//May crash if final character of path is a slash, but that shouldn't happen...
	return path.substr(newFirstCharacter);
}

std::string RemoveTrailingCharacters(const std::string& str, char character)
{
	//Get position of last character that isn't character to be removed
	size_t size;
	for (size = str.size() - 1; size != std::numeric_limits<size_t>::max(); --size)
	{
		if (str[size] != character)
		{
			++size;
			break;
		}
	}

	if (size != str.size())
		return str.substr(0u, size);
	else
		return str;
}

std::string RemovePrecedingCharacters(const std::string& str, char character)
{
	//Get position of last character that isn't character to be removed
	size_t start;
	for (start = 0; start < str.size(); ++start)
	{
		if (str[start] != character)
		{
			break;
		}
	}

	if (start != 0)
		return str.substr(start);
	else
		return str;
}