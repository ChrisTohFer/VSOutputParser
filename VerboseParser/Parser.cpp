#include "Parser.h"

std::vector<VERBOSE::LOG_CONTENT>& VERBOSE::storage()
{
	static std::vector<LOG_CONTENT> s;
	return s;
}

void VERBOSE::add_to_storage(LOG_CONTENT log)
{
	storage().push_back(std::move(log));
}

void VERBOSE::add_to_storage(std::vector<LOG_CONTENT> logs)
{
	storage().insert(storage().end(), logs.begin(), logs.end());
}

void VERBOSE::parse_and_add(const std::wstring& path)
{
	add_to_storage(ParseLogFile(path));
}

void VERBOSE::parse_and_add(const std::vector<std::wstring>& paths)
{
	add_to_storage(ParseLogFiles(paths));
}