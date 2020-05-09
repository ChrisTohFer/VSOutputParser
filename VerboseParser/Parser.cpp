#include "Parser.h"
#include "GenericFunctions/StringFunctions.h"

std::wstring VERBOSE::LOG_KEY::name()
{
	return GetNameFromPath(path);
}

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

std::vector<VERBOSE::LOG_KEY> VERBOSE::log_files()
{
	auto& logs = storage();

	std::vector<LOG_KEY> keys;
	auto size = logs.size();

	for (auto i = 0u; i < size; ++i)
	{
		auto& log = logs[i];
		keys.push_back({int(i), log.wpath});
	}

	return keys;
}