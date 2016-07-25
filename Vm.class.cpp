#include "Vm.class.hpp"

Vm::Vm(void)
{
	this->type.insert(std::make_pair("INT8", INT8));
	this->type.insert(std::make_pair("INT16", INT16));
	this->type.insert(std::make_pair("INT32", INT32));
	this->type.insert(std::make_pair("FLOAT", FLOAT));
	this->type.insert(std::make_pair("DOUBLE", DOUBLE));

	this->typeString.insert(std::make_pair(INT8, "INT8"));
	this->typeString.insert(std::make_pair(INT16, "INT16"));
	this->typeString.insert(std::make_pair(INT32, "INT32"));
	this->typeString.insert(std::make_pair(FLOAT, "FLOAT"));
	this->typeString.insert(std::make_pair(DOUBLE, "DOUBLE"));

	this->fmap.insert(std::make_pair("pop", &Vm::pop));
	this->fmap.insert(std::make_pair("dump", &Vm::dump));
	this->fmap.insert(std::make_pair("add", &Vm::add));
	this->fmap.insert(std::make_pair("sub", &Vm::sub));
	this->fmap.insert(std::make_pair("mul", &Vm::mul));
	this->fmap.insert(std::make_pair("div", &Vm::div));
	this->fmap.insert(std::make_pair("mod", &Vm::mod));
	this->fmap.insert(std::make_pair("print", &Vm::print));

	this->opmap.insert(std::make_pair(INT8, &Vm::createInt8));
	this->opmap.insert(std::make_pair(INT16, &Vm::createInt16));
	this->opmap.insert(std::make_pair(INT32, &Vm::createInt32));
	this->opmap.insert(std::make_pair(FLOAT, &Vm::createFloat));
	this->opmap.insert(std::make_pair(DOUBLE, &Vm::createDouble));
}

Vm::~Vm(void)
{
}

Vm::Vm(Vm const & src)
{
	*this = src;
}


void    Vm::start(Parser *parser)
{
	int 	i = 0;
	int 	size = parser->getCmd().size();

	while (i < size)
	{
		std::string cmd;
		cmd = parser->getCmd().front();
		if (cmd == "exit")
			return ;
		if (cmd == "push")
		{
			this->push(parser->getType().front(), parser->getValue().front());
		}
		else if (cmd == "assert")
		{
			this->assert(parser->getType().front(), parser->getValue().front());
		}
		else
		{
			(this->*fmap[parser->getCmd().front()])();
		} 	
		parser->popFront();
		i++;
	}
	throw(Exception("Command exit not found"));
}

IOperand		*Vm::createInt8(std::string const & value) const
{
	return (new Operand<char>(INT8, value));
}

IOperand		*Vm::createInt16(std::string const & value) const
{
	return (new Operand<short>(INT16, value));
}

IOperand		*Vm::createInt32(std::string const & value) const
{
	return (new Operand<int>(INT32, value));
}

IOperand		*Vm::createFloat(std::string const & value) const
{
	return (new Operand<float>(FLOAT, value));
}

IOperand		*Vm::createDouble(std::string const & value) const
{
	return (new Operand<double>(DOUBLE, value));
}


void	Vm::checkLimitsValue(std::string type, std::string lvalue)
{
	double value;

	try 
	{
		value = std::stod(lvalue);
	}
	catch (const std::out_of_range&)
	{
        std::cerr << "Error : Value" + lvalue + " is out of range\n";
        exit(-1);
	}
	if (type == "INT8")
	{
		if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
			throw(Exception("Value " + lvalue + " is not in INT8 range"));
	}
	else if (type == "INT16")
	{
		if (value < std::numeric_limits<short>::min() || value > std::numeric_limits<short>::max())
			throw(Exception("Value " + lvalue + " is not in INT16 range"));
	}
	else if (type == "INT32")
	{
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
			throw(Exception("Value " + lvalue + " is not in INT32 range"));
	}
	else if (type == "FLOAT")
	{
		if (value < std::numeric_limits<float>::min() || value > std::numeric_limits<float>::max())
			throw(Exception("Value " + lvalue + " is not in FLOAT range"));
	}
}

void    Vm::push(std::string type, std::string value)
{
	this->checkLimitsValue(type, value);
	this->_operand.push_front((this->*opmap[this->type[type]])(value));
}

void    Vm::assert(std::string type, std::string value)
{
	if (this->_operand.front()->toString() != value || this->_operand.front()->getType() != this->type[type])
		throw(Exception("assert error"));
}

void    Vm::pop()
{
	if (this->_operand.size() == 0)
		throw(Exception("Can't pop empty stack"));
	this->_operand.pop_front();
}

void    Vm::dump()
{
	std::list<IOperand*>::iterator i;
	for(i = this->_operand.begin(); i != this->_operand.end(); i++)
		std::cout << (*i)->toString() << std::endl;
}

void    Vm::add()
{
	IOperand const *res;
	IOperand *tmp1;
	IOperand *tmp2;
	if (this->_operand.size() < 2)
		throw(Exception("Can't do an addition with less than 2 values on the stack"));
	tmp1 = this->_operand.front();
	this->pop();
	tmp2 = this->_operand.front();
	this->pop();
	res = *tmp2 + *tmp1;
	this->push(this->typeString[res->getType()], res->toString());
}

void    Vm::sub()
{
	IOperand const *res;
	IOperand *tmp1;
	IOperand *tmp2;
	if (this->_operand.size() < 2)
		throw(Exception("Can't do a substraction with less than 2 values on the stack"));
	tmp1 = this->_operand.front();
	this->pop();
	tmp2 = this->_operand.front();
	this->pop();
	res = *tmp2 - *tmp1;
	this->push(this->typeString[res->getType()], res->toString());
}

void    Vm::mul()
{
	IOperand const *res;
	IOperand *tmp1;
	IOperand *tmp2;
	if (this->_operand.size() < 2)
		throw(Exception("Can't do a multiplication with less than 2 values on the stack"));
	tmp1 = this->_operand.front();
	this->pop();
	tmp2 = this->_operand.front();
	this->pop();
	res = *tmp2 * *tmp1;
	this->push(this->typeString[res->getType()], res->toString());
}

void    Vm::div()
{
	IOperand const *res;
	IOperand *tmp1;
	IOperand *tmp2;
	if (this->_operand.size() < 2)
		throw(Exception("Can't do a division with less than 2 values on the stack"));
	tmp1 = this->_operand.front();
	this->pop();
	if (tmp1->toString() == "0")
		throw(Exception("Can't do a division by 0"));
	tmp2 = this->_operand.front();
	this->pop();
	res = *tmp2 / *tmp1;
	this->push(this->typeString[res->getType()], res->toString());
}

void    Vm::mod()
{
	IOperand const *res;
	IOperand *tmp1;
	IOperand *tmp2;
	if (this->_operand.size() < 2)
		throw(Exception("Can't do a modulo with less than 2 values on the stack"));
	tmp1 = this->_operand.front();
	this->pop();
	if (tmp1->toString() == "0")
		throw(Exception("Can't do a modulo by 0"));
	tmp2 = this->_operand.front();
	this->pop();
	res = *tmp2 % *tmp1;
	this->push(this->typeString[res->getType()], res->toString());
}

void    Vm::print()
{
	if (this->_operand.size() == 0)
		throw(Exception("No value to print"));
	if (this->_operand.front()->getType() != INT8)
		throw(Exception("You can only print a INT8"));

	std::istringstream 	iss;
	char				c;
	double 				n;

	iss.str(this->_operand.front()->toString());
	iss >> n;
	c = n;

	std::cout << c << std::endl;
}

Vm&				Vm::operator=(Vm const & rhs)
{
	this->type = rhs.type;
	this->typeString = rhs.typeString;
	this->fmap = rhs.fmap;
	this->opmap = rhs.opmap;
	this->_operand = rhs.getOperand();
	return (*this);
}

std::list<IOperand*> Vm::getOperand() const
{
	return (this->_operand);
}