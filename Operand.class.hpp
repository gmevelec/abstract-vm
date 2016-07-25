#ifndef OPERAND_CLASS_HPP
# define  OPERAND_CLASS_HPP

# include "IOperand.class.hpp"

template <typename T>
class Operand : public IOperand
{
public:
	Operand(eOperandType const &, std::string const &);
	virtual ~Operand();
	Operand(Operand const & src);

	T					getValue() const;
	std::string const	&toString() const;
	int					getPrecision() const;
	eOperandType		getType() const;
	std::string 		getStringValue() const;
	std::string 		getStringType() const;

	IOperand		*operator+(const IOperand &rhs) const;
	IOperand		*operator-(const IOperand &rhs) const;
	IOperand		*operator*(const IOperand &rhs) const;
	IOperand		*operator/(const IOperand &rhs) const;
	IOperand		*operator%(const IOperand &rhs) const;
	
	Operand*			operator=(const Operand &rhs);

	void 				setStringValue(std::string);
	void				setType(eOperandType);
	void				setValue(T);

private:
	Operand();
	eOperandType	_type;
	T 				_value;
	std::string		_stringValue;
};

template <typename T>
Operand<T>::Operand(eOperandType const & type, std::string const & value)
{
	this->_type = type;
	this->_stringValue = value;
}

template <typename T>
Operand<T>::~Operand()
{
}

template <typename T>
Operand<T>::Operand(Operand const & src)
{
	*this = src;
}

template <typename T>
IOperand	*Operand<T>::operator+(const IOperand &rhs) const
{
	eOperandType	type;
	std::string		res;
	double 			n1;
	double 			n2;
	std::istringstream iss;

	type = this->getType();
	if (type < rhs.getType())
		type = rhs.getType();

	iss.str(this->toString());
	iss >> n1;
	iss.clear();
	iss.str(rhs.toString());
	iss >> n2;
	std::ostringstream oss;
	oss << n2 + n1;
	res = oss.str();

	return (new Operand<T>(type, res));
}

template <typename T>
IOperand	*Operand<T>::operator-(const IOperand &rhs) const
{
	eOperandType	type;
	std::string		res;
	double 			n1;
	double 			n2;
	std::istringstream iss;

	type = this->getType();
	if (type < rhs.getType())
		type = rhs.getType();

	iss.str(this->toString());
	iss >> n1;
	iss.clear();
	iss.str(rhs.toString());
	iss >> n2;
	std::ostringstream oss;
	oss << n2 - n1;
	res = oss.str();

	return (new Operand<T>(type, res));
}

template <typename T>
IOperand	*Operand<T>::operator*(const IOperand &rhs) const
{
	eOperandType	type;
	std::string		res;
	double 			n1;
	double 			n2;
	std::istringstream iss;

	type = this->getType();
	if (type < rhs.getType())
		type = rhs.getType();

	iss.str(this->toString());
	iss >> n1;
	iss.clear();
	iss.str(rhs.toString());
	iss >> n2;
	std::ostringstream oss;
	oss << n2 * n1;
	res = oss.str();

	return (new Operand<T>(type, res));
}

template <typename T>
IOperand	*Operand<T>::operator/(const IOperand &rhs) const
{
	eOperandType	type;
	std::string		res;
	int 			n1;
	int 			n2;
	std::istringstream iss;

	type = this->getType();
	if (type < rhs.getType())
		type = rhs.getType();

	iss.str(this->toString());
	iss >> n1;
	iss.clear();
	iss.str(rhs.toString());
	iss >> n2;
	std::ostringstream oss;
	oss << n2 / n1;
	res = oss.str();

	return (new Operand<T>(type, res));
}

template <typename T>
IOperand	*Operand<T>::operator%(const IOperand &rhs) const
{
	eOperandType	type;
	std::string		res;
	int 			n1;
	int 			n2;
	std::istringstream iss;

	type = this->getType();
	if (type < rhs.getType())
		type = rhs.getType();

	iss.str(this->toString());
	iss >> n1;
	iss.clear();
	iss.str(rhs.toString());
	iss >> n2;
	std::ostringstream oss;
	oss << (n2 % n1);
	res = oss.str();

	return (new Operand<T>(type, res));
}

template <typename T>
int				Operand<T>::getPrecision() const
{
	return (static_cast<int>(this->_type));
}


template <typename T>
std::string	const &Operand<T>::toString() const
{
	return (this->_stringValue);
}

//
//	GETTERS
//

template <typename T>
std::string 	Operand<T>::getStringValue() const { return (this->_stringValue);}
template <typename T>
eOperandType 	Operand<T>::getType() const { return (this->_type);}
template <typename T>
T 	 			Operand<T>::getValue() const { return (this->_value);}

//
// SETTERS
//
template <typename T>
void 		Operand<T>::setStringValue(std::string stringValue)
{
	this->_stringValue = stringValue;
}

template <typename T>
void 		Operand<T>::setType(eOperandType type)
{
	this->_type = type;
}

template <typename T>
void 		Operand<T>::setValue(T value)
{
	this->_value = value;
}


template <typename T>
Operand<T>*		Operand<T>::operator=(Operand const & rhs)
{
	this->_type = rhs.getType();
	this->_value = rhs.getValue();
	this->_stringValue = rhs.getStringValue();	
}

#endif
