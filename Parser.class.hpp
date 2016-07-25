#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <iostream>
#include <fstream>
#include <list>
#include <regex>
#include <limits>
#include "Exception.class.hpp"

# define CALL_PARSER_FN(object, ptrToMember) ((object)->*(ptrToMember))

class Parser
{
public:

	Parser();
	Parser(Parser const & src);
	virtual ~Parser();

	void						parsePush(std::string line, int nline);
	void						parseAssert(std::string line, int nline);
	void						parsePop(std::string line, int nline);
	void						parseDump(std::string line, int nline);
	void						parseAdd(std::string line, int nline);
	void						parseSub(std::string line, int nline);
	void						parseMul(std::string line, int nline);
	void						parseDiv(std::string line, int nline);
	void						parseMod(std::string line, int nline);
	void						parsePrint(std::string line, int nline);
	void						parseCom(std::string line, int nline);
	void						parseExit(std::string line, int nline);
	
	void						checkValue(std::string line, int nline);
	void						checkValueLimits(int nline);
	void						parseFile(const std::string& name);

	void						popFront();

	void						print(std::list<std::string> list);
	void						print(std::list<std::string>, std::list<std::string>, std::list<std::string>);

	Parser&						operator=(Parser const & rhs);
	
	std::list<std::string>		getCmd() const;
	std::list<std::string>		getType() const;
	std::list<std::string>		getValue() const;
	void						setCmd(std::string str);
	void						setType(std::string str);
	void						setValue(std::string str);

private:

	std::list<std::string>		_cmd;
	std::list<std::string>		_type;
	std::list<std::string>		_value;

};

typedef void (Parser::*ParserInstruction) (std::string, int);

#endif