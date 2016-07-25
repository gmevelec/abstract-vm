#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include "Parser.class.hpp"
#include "Operand.class.hpp"
#include "Vm.class.hpp"

inline bool testFileExist(const std::string& name)
{
	return (access(name.c_str(), F_OK) != -1);
}

void		parseFile(const std::string& name)
{

	Parser			*parser = new Parser();
	Vm				vm;

	parser->parseFile(name);
	vm.start(parser);
	delete parser;
}

int main(int ac, char **av)
{
	try
	{
		if (ac == 1)
		{
			std::cout << "READ ON 0" << std::endl;
			if (testFileExist("sample.avm"))
				remove("sample.avm");
			std::ofstream file("sample.avm");
		    for (std::string line; std::getline(std::cin, line);)
		    {
		    	if (line == ";;")
		    		break ;
		        file << line << std::endl;
		    }
			file.close();
			parseFile("sample.avm");
		}
		else if (ac == 2)
		{
			std::cout << "READ ON " << av[1] << std::endl;
			if (testFileExist(av[1]))
				parseFile(av[1]);
			else
				throw(Exception("File doesn't exist"));
		}
	}
	catch(Exception const & error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
	}

	return 0;
}
