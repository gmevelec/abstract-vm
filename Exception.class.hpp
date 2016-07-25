#ifndef EXCEPTION_CLASS_HPP
# define EXCEPTION_CLASS_HPP

#include <iostream>
#include <sstream>
#include <exception>

class Exception : public std::exception
{
public:
	Exception(Exception const & src);
	Exception(std::string const & msg) throw();
	virtual ~Exception() throw();
	virtual const char *what() const throw();

	Exception& 		operator=(Exception const & src);
	std::string		getMsg() const;
	
private:
	Exception();
	std::string 	_msg;
};

#endif
