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

	//contains state information used by parsing functions regarding a single project
	struct PROJECT_PARSING_STATE
	{
		int currentLib = 0;
		std::string currentSymbol;
		std::set<std::string> defaultLibs;
	};

	//contains state information used by parsing functions
	struct PARSING_STATE
	{
		LOG_CONTENT& log;

		int currentProject = 0;
		std::vector<PROJECT_PARSING_STATE> project_states;

		PARSING_STATE(LOG_CONTENT& logArg)
			: log(logArg)
		{}

		PROJECT& project()
		{
			return log.projects[currentProject];
		}
		PROJECT_PARSING_STATE& project_state()
		{
			return project_states[currentProject];
		}
		LIBRARY& library()
		{
			return project().libraries[project_state().currentLib];
		}
		SYMBOL& symbol()
		{
			return library().symbols[project_state().currentSymbol];
		}
	};

	//identify defaultlibs
	void ParseProcessedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		if (term.size() > 12 && term.substr(0u, 12u) == "/DEFAULTLIB:")
		{
			state.project_state().defaultLibs.emplace(term.substr(12u));
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

		//Create references to relevant containers
		auto& project = state.project();
		auto& libmap = project.libraryMap;
		auto& libs = project.libraries;

		auto library = libmap.find(term);
		if (library == libmap.end())
		{
			//Need to create new library entry
			libmap.emplace(std::make_pair(term, int(libs.size())));
			libs.push_back(LIBRARY(term));
			state.project_state().currentLib = libs.size() - 1;
			state.library().parent = state.project().name;

			//Check if library is a default library
			auto& defLibs = state.project_state().defaultLibs;
			auto name = GetNameFromPath(term);
			if (defLibs.find(name) != defLibs.end())
				state.library().defaultLib = true;
		}
		else
		{
			//Library already exists
			state.project_state().currentLib = libmap[term];
		}
	}

	//identify symbols
	void ParseFoundLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		auto& symbolMap = state.project().libraries[state.project_state().currentLib].symbols;

		auto symbol = symbolMap.find(term);
		if (symbol == symbolMap.end())
		{
			symbolMap.emplace(term, SYMBOL());
		}
		state.project_state().currentSymbol = term;
	}

	//identify references to the current symbol and lib
	void ParseReferencedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(4);	//ignore ' in '

		std::string term;
		std::getline(lineStream, term);

		auto& lib = state.project().libraries[state.project_state().currentLib];
		lib.references.emplace(term);
		lib.symbols[state.project_state().currentSymbol].references.emplace(term);
	}

	//identify whether lib is a dll (could also look into saving names of .obj files for later analysis)
	void ParseLoadedLine(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(1);	//Ignore space

		std::string term;
		std::getline(lineStream, term);

		if (term.size() > 5u && term.substr(term.size() - 5u) == ".dll)")	//if term ends in .dll)
			state.project().libraries[state.project_state().currentLib].type = LIB_TYPE::DLL;
	}

	//Identify the name of a project in a multi project file
	void ParseName(PARSING_STATE& state, std::istringstream& lineStream)
	{
		lineStream.ignore(24);	//Ignore " Build started: Project: "
		
		lineStream >> state.project().name;
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

		content.projects.reserve(100); // this is absolute jank, but will prevent pointers from being invalidated

		//Check if we are parsing multiple projects in a single log file by searching for visual studio "n>" project notation
		bool multiple_projects;

		{
			char buffer[2];

			//Read start of stream and reset position
			auto start = logfile.tellg();
			logfile.read(buffer, 2);
			logfile.seekg(start);

			multiple_projects = (buffer[0] == '1' && buffer[1] == '>');
		}

		if (!multiple_projects)
		{
			content.projects.push_back(PROJECT());
			state.project_states.push_back(PROJECT_PARSING_STATE());
			state.currentProject = 0;
		}

		//debug var
		auto linenumber = 0;

		//loops through lines of file, exits loop when logfile is in an error state (eof)
		std::string line;
		while (std::getline(logfile, line))
		{
			++linenumber;
			std::istringstream lineStream;
			
			//If there are multiple projects, find out which project this line refers to and remove the number from the linestream
			if (multiple_projects)
			{
				auto num_length = line.find_first_of('>');
				
				if (num_length > 3 || !std::isdigit(line[0]))	//We probably aren't reading a project number in this case
					continue;

				state.currentProject = std::stoi(line.substr(0, num_length)) - 1; //number counts from 1

				if (state.currentProject >= content.projects.size())
				{
					content.projects.push_back(PROJECT());
					state.project_states.push_back(PROJECT_PARSING_STATE());
				}

				if (line.size() == num_length + 1)	//The line contains no additional information
					continue;
				
				lineStream.str(line.substr(num_length + 1));
			}
			else
			{
				lineStream.str(line);
			}

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
			else if (term == "------")
			{
				ParseName(state, lineStream);
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