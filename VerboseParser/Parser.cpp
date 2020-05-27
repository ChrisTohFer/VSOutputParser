#include "Parser.h"
#include "GenericFunctions/StringFunctions.h"

std::wstring VERBOSE::LOG_KEY::name()
{
	return GetNameFromPath(path);
}

VERBOSE::LOG_CONTENT VERBOSE::LOG_KEY::log()
{
	return storage()[index];
}

VERBOSE::PROJECT VERBOSE::PROJECT_KEY::project()
{
	return storage()[log_index].projects[proj_index];
}

VERBOSE::LIBRARY VERBOSE::LIBRARY_KEY::library()
{
	return storage()[log_index].projects[proj_index].libraries[lib_index];
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

std::vector<VERBOSE::PROJECT_KEY> VERBOSE::projects(std::vector<LOG_KEY> logs)
{
	std::vector<PROJECT_KEY> result;

	for (auto i = 0u; i < logs.size(); ++i)
	{
		auto log = logs[i].log();
		for (auto j = 0; j < log.projects.size(); ++j)
		{
			auto project = log.projects[j];
			result.push_back({ logs[i].index, j, project.name });
		}
	}

	return result;
}

std::vector<VERBOSE::LIBRARY> VERBOSE::libraries(std::vector<PROJECT_KEY> projects)
{
	std::vector<VERBOSE::LIBRARY> result;

	for (auto i = 0u; i < projects.size(); ++i)
	{
		auto project = projects[i].project();
		for (auto j = 0u; j < project.libraries.size(); ++j)
		{
			result.push_back(project.libraries[j]);
		}
	}

	return result;
}

