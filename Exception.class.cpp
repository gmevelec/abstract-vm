#include "Exception.class.hpp"

Exception::Exception(std::string const &msg) throw()
{
	this->_msg = msg;
}

Exception::Exception(Exception const & src)
{
	*this = src;
}

Exception::~Exception() throw()
{}

const char 		*Exception::what() const throw()
{
	return (this->_msg.c_str());
}

Exception& 		Exception::operator=(Exception const & rhs)
{
	this->_msg = rhs.getMsg();
	return *this;
}

std::string		Exception::getMsg() const {return this->_msg;}