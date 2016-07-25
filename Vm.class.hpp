#ifndef VM_CLASS_HPP
# define VM_CLASS_HPP

# include <iostream>
# include <map>
# include "Parser.class.hpp"
//# include "IOperand.class.hpp"
# include "Operand.class.hpp"

class Vm
{
public:

	Vm();
	~Vm();
	Vm(Vm const & src);

	std::map<std::string, eOperandType> type;
	std::map<eOperandType, std::string> typeString;

	typedef void (Vm::*VmInstruction) ();
	std::map<std::string, VmInstruction> fmap;


	typedef IOperand *(Vm::*const OpCreation) (std::string const &) const;
	std::map<eOperandType, OpCreation> opmap;

	void		push(std::string, std::string value);
	void		assert(std::string, std::string value);
	void		pop();
	void		dump();
	void		add();
	void		sub();
	void		mul();
	void		div();
	void		mod();
	void		print();

	void    	start(Parser *parser);
	void		printStack();
	void		checkLimitsValue(std::string type, std::string value);

	Vm& 		operator=(Vm const & rhs);

	std::list<IOperand*> 	getOperand() const;

private:

	std::list<IOperand*>		_operand;

	IOperand	*createInt8(std::string const & value) const;
	IOperand	*createInt16(std::string const & value) const;
	IOperand	*createInt32(std::string const & value) const;
	IOperand	*createFloat(std::string const & value) const;
	IOperand	*createDouble(std::string const & value) const;

};

#endif
