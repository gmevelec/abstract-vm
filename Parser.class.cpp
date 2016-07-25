#include "Parser.class.hpp"

ParserInstruction 	ptr[] = {&Parser::parsePush,
						 &Parser::parseAssert,
						 &Parser::parsePop,
						 &Parser::parseDump,
						 &Parser::parseAdd,
						 &Parser::parseSub,
						 &Parser::parseMul,
						 &Parser::parseDiv,
						 &Parser::parseMod,
						 &Parser::parsePrint,
						 &Parser::parseCom,
						 &Parser::parseExit,
						};

//
//	CONSTRUCTOR / DESTRUCTOR
//

Parser::Parser()
{
}

Parser::Parser(Parser const & src)
{
	*this = src;
}

Parser::~Parser()
{
}

//
// ARRAY OF POINTER TO MEMBER FUNCTION
//

void						Parser::parsePush(std::string line, int nline)
{
	this->setCmd("push");
	this->checkValue(line, nline);
}
void						Parser::parseAssert(std::string line, int nline)
{
	this->setCmd("assert");
	this->checkValue(line, nline);
}

void						Parser::parsePop(std::string line, int nline)
{
	this->setCmd("pop");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseDump(std::string line, int nline)
{
	this->setCmd("dump");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseAdd(std::string line, int nline)
{
	this->setCmd("add");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseSub(std::string line, int nline)
{
	this->setCmd("sub");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseMul(std::string line, int nline)
{
	this->setCmd("mul");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseDiv(std::string line, int nline)
{
	this->setCmd("div");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseMod(std::string line, int nline)
{
	this->setCmd("mod");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parsePrint(std::string line, int nline)
{
	this->setCmd("print");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseCom(std::string line, int nline)
{
	static_cast<void>(line);
	static_cast<void>(nline);
}

void						Parser::parseExit(std::string line, int nline)
{
	this->setCmd("exit");
	this->setType("null");
	this->setValue("null");
	static_cast<void>(line);
	static_cast<void>(nline);
}

//
// GET THE VALUE FROM THE INSTRUCTION * between () * 
//

std::string 				getValueFromInstruction(std::string line)
{
	int 			i = 0;
	std::string 	tmp;

	while (line[i] != '(')
		i++;
	i++;
	while (line[i] != ')')
	{
		tmp+=line[i];
		i++;
	}
	return (tmp);
}

//
// CHECK IF THE VALUE IS CORRECT DEPENDING OF THE TYPE
// IF IT'S CORRECT ASSIGN VALUE
// IF NOT THROW ERROR
//

void						Parser::checkValueLimits(int nline)
{
	double value;

	try 
	{
		value = std::stod(this->getValue().back());
	}
	catch (const std::out_of_range&)
	{
        std::cerr << "Line " + std::to_string(nline) + ": " + this->getValue().back() + " is out of range\n";
        exit(-1);
	}
	if (this->getType().back() == "INT8")
	{
		if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
			throw(Exception("Line " + std::to_string(nline) + ": Value " + this->getValue().back() + " is not in INT8 range"));
	}
	else if (this->getType().back() == "INT16")
	{
		if (value < std::numeric_limits<short>::min() || value > std::numeric_limits<short>::max())
			throw(Exception("Line " + std::to_string(nline) + ": Value " + this->getValue().back() + " is not in INT16 range"));
	}
	else if (this->getType().back() == "INT32")
	{
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
			throw(Exception("Line " + std::to_string(nline) + ": Value " + this->getValue().back() + " is not in INT32 range"));
	}
	else if (this->getType().back() == "FLOAT")
	{
		if (value < std::numeric_limits<float>::min() || value > std::numeric_limits<float>::max())
			throw(Exception("Line " + std::to_string(nline) + ": Value " + this->getValue().back() + " is not in FLOAT range"));
	}
}

void						Parser::checkValue(std::string line, int nline)
{
	std::string regexInt8 = "^(push|assert)( )(int8)(\\(-?[0-9]+\\))( *|\t*)((;)(.*))?$";
	std::string regexInt16 = "^(push|assert)( )(int16)(\\(-?[0-9]+\\))( *|\t*)((;)(.*))?$";
	std::string regexInt32 = "^(push|assert)( )(int32)(\\(-?[0-9]+\\))( *|\t*)((;)(.*))?$";
	std::string regexFloat = "^(push|assert)( )(float)(\\(-?[0-9]+(\\.?[0-9]+)?\\))( *|\t*)((;)(.*))?$";
	std::string regexDouble = "^(push|assert)( )(double)(\\(-?[0-9]+(\\.?[0-9]+)?\\))( *|\t*)((;)(.*))?$";

	if (std::regex_match(line, std::regex(regexInt8)))
	{
		this->setType("INT8");
		this->setValue(getValueFromInstruction(line));
		this->checkValueLimits(nline);
	}
	else if (std::regex_match(line, std::regex(regexInt16)))
	{
		this->setType("INT16");
		this->setValue(getValueFromInstruction(line));
		this->checkValueLimits(nline);
	}
	else if (std::regex_match(line, std::regex(regexInt32)))
	{
		this->setType("INT32");
		this->setValue(getValueFromInstruction(line));
		this->checkValueLimits(nline);
	}
	else if (std::regex_match(line, std::regex(regexFloat)))
	{
		this->setType("FLOAT");
		this->setValue(getValueFromInstruction(line));
		this->checkValueLimits(nline);
	}
	else if (std::regex_match(line, std::regex(regexDouble)))
	{
		this->setType("DOUBLE");
		this->setValue(getValueFromInstruction(line));
		this->checkValueLimits(nline);
	}
	else
	{
		std::string			error;
		std::stringstream 	sstm;
		sstm << "Line " << nline << ": Type error: " << line;
		error = sstm.str();
		throw (Exception(error));
	}
}

//
// CHECK IF THE LINE MATCH WITH AN INSTRUCTION
// IF YES FILL THE CMD, TYPE, VALUE
// IF NOT THROW ERROR
//

void				Parser::parseFile(const std::string& name)
{
	std::ifstream				file(name);
	std::string					line;
	std::regex 					regex[] = {static_cast<std::regex>("^(push)(.*)$"),
								static_cast<std::regex>("^(assert)(.*)$"),		
								static_cast<std::regex>("^(pop)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(dump)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(add)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(sub)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(mul)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(div)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(mod)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^(print)( *|\t*)((;)(.*))?$"),		
								static_cast<std::regex>("^( *|\t*)?(;)(.*)$"),		
								static_cast<std::regex>("^(exit)( *|\t*)((;)(.*))?$"),		
											};

	int 		nline = 1;
	while (std::getline(file, line))
	{
		int 		i = 0;
		int 		k;
		while (i < 12)
		{
			k = 0;
			if (std::regex_match(line, regex[i]))
			{
				CALL_PARSER_FN(this, ptr[i])(line, nline);
				k = 1;
				break;
			}
			i++;
		}
		if (k == 0 && line[0] != '\0')
		{
			std::string			error;
			std::stringstream 	sstm;
			sstm << "Line " << nline << ": Command not found: " << line;
			error = sstm.str();
			throw (Exception(error));
		}
		nline++;
	}
	file.close();
	std::cout << "PARSING DONE" << std::endl;
}

void						Parser::popFront()
{
	this->_cmd.pop_front();
	this->_type.pop_front();
	this->_value.pop_front();
}

//
// PRINT ALL LISTS
//

void						Parser::print(std::list<std::string> cmd, std::list<std::string> type, std::list<std::string> value)
{
	std::list<std::string>::const_iterator i;
	std::list<std::string>::const_iterator j = type.begin();
	std::list<std::string>::const_iterator k = value.begin();

	for(i = cmd.begin(); i != cmd.end(); i++)
	{
		if (*j != "null" && *k != "null")
			std::cout << *i << "<" << *j << ">" << "(" << *k << ")" << std::endl;
		else
			std::cout << *i << std::endl;
		j++;
		k++;
	}
}

//
// PRINT ONE LIST
//

void						Parser::print(std::list<std::string> list)
{
	std::list<std::string>::const_iterator i;

	for(i = list.begin(); i != list.end(); i++)
	{
		if (*i != "null")
			std::cout << *i << std::endl;
	}
}

Parser& 					Parser::operator=(Parser const & rhs)
{
	this->_cmd = rhs.getCmd();
	this->_type = rhs.getType();
	this->_value = rhs.getValue();
	return (*this);
}

//
// GETTERS
//

std::list<std::string>		Parser::getCmd() const { return (this->_cmd);}
std::list<std::string>		Parser::getType() const { return (this->_type);}
std::list<std::string>		Parser::getValue() const { return (this->_value);}

//
// SETTERS
//

void						Parser::setCmd(std::string str)
{
	this->_cmd.push_back(str);
}

void						Parser::setType(std::string str)
{
	this->_type.push_back(str);
}

void						Parser::setValue(std::string str)
{
	this->_value.push_back(str);
}