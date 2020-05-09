#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <thread>
#include <type_traits>

#include "VerboseParserTypes.h"
#include "GenericFunctions/StringFunctions.h"

namespace
{
	using namespace VERBOSE;

	//contains state information used by parsing functions
	struct PARSING_STATE
	{
		LOG_CONTENT& log;
		LIBRARY* currentLib = nullptr;
		SYMBOL* currentSymbol = nullptr;
		std::set<std::string> defaultLibs;

		PARSING_STATE(LOG_CONTENT& logArg)
			: log(logArg)
		{}
	};

	//identify defaultlibs
	void ParseProcessedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		if (term.size() > 12 && term.substr(0u, 12u) == "/DEFAULTLIB:")
		{
			state.defaultLibs.emplace(term.substr(12u));
		}
	}

	//identify libs and point to current lib
	void ParseSearchingLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);
		term = RemoveTrailingCharacters(term, ':');

		if (term == "libraries")
			return;

		auto& libmap = state.log.libraryMap;
		auto& libs = state.log.libraries;

		auto library = libmap.find(term);
		if (library == libmap.end())
		{
			//Need to create new library entry
			libmap.emplace(std::make_pair(term, int(libs.size())));
			libs.push_back(LIBRARY(term));
			state.currentLib = &libs.back();

			//Check if library is a default library
			auto& defLibs = state.defaultLibs;
			auto name = GetNameFromPath(term);
			if (defLibs.find(name) != defLibs.end())
				state.currentLib->defaultLib = true;
		}
		else
		{
			//Library already exists
			state.currentLib = &(libs[libmap[term]]);
		}
	}

	//identify symbols
	void ParseFoundLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		auto& symbolMap = state.currentLib->symbols;

		auto symbol = symbolMap.find(term);
		if (symbol == symbolMap.end())
		{
			symbolMap.emplace(term, SYMBOL());
			state.currentSymbol = &(symbolMap[term]);
		}
		else
		{
			state.currentSymbol = &(symbol->second);
		}
	}

	//identify references to the current symbol and lib
	void ParseReferencedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(4);	//ignore ' in '

		std::string term;
		std::getline(lineStream, term);

		state.currentLib->references.emplace(term);
		state.currentSymbol->references.emplace(term);
	}

	//identify whether lib is a dll (could also look into saving names of .obj files for later analysis)
	void ParseLoadedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		if (term.size() > 5u && term.substr(term.size() - 5u) == ".dll)")	//if term ends in .dll)
			state.currentLib->type = LIBRARY::TYPE::DLL;
	}

}

namespace VERBOSE
{

	//parse the entire log file
	template<typename CHAR_TYPE>
	LOG_CONTENT ParseLogFile(const std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>& path)
	{
		std::ifstream logfile(path);
		LOG_CONTENT content;
		if constexpr (std::is_same<CHAR_TYPE, wchar_t>())
			content.wpath = path;
		else
			content.path = path;

		PARSING_STATE state(content);

		//loops through lines of file, exits loop when logfile is in an error state (eof)
		std::string line;
		while (std::getline(logfile, line))
		{
			std::istringstream lineStream(line);
			std::string term;

			lineStream >> term;
			if (term == "Processed")
			{
				ParseProcessedLine(state, lineStream);
			}
			else if (term == "Searching")
			{
				ParseSearchingLine(state, lineStream);
			}
			else if (term == "Found")
			{
				ParseFoundLine(state, lineStream);
			}
			else if (term == "Referenced")
			{
				ParseReferencedLine(state, lineStream);
			}
			else if (term == "Loaded")
			{
				ParseLoadedLine(state, lineStream);
			}
		}

		logfile.close();

		return content;
	}

	//parse multiple log files using multiple threads
	template<typename CHAR_TYPE>
	std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>>& paths)
	{
		//set up storage for each thread
		std::vector<LOG_CONTENT> logs;
		std::vector<std::thread> threads;

		for (size_t i = 0u; i < paths.size(); ++i)
		{
			logs.push_back(LOG_CONTENT());
			threads.push_back(std::thread());
		}

		//define thread execution
		auto ThreadMethod = [&](size_t i)
		{
			logs[i] = ParseLogFile(paths[i]);
		};

		//execute
		for (size_t i = 0u; i < paths.size(); ++i)
		{
			std::thread t(ThreadMethod, i);
			threads[i] = std::move(t);
		}

		//join then return
		for (size_t i = 0u; i < paths.size(); ++i)
		{
			threads[i].join();
		}

		return logs;
	}

	//instantiate functions templates for std::string and std::wstring

	template LOG_CONTENT ParseLogFile(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& path);
	template LOG_CONTENT ParseLogFile(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>& path);
	template std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>& paths);
	template std::vector<LOG_CONTENT> ParseLogFiles(const std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>>& paths);

}