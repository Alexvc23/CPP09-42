#include "RPN.hpp"

// Constructors
RPN::RPN()
{
	_s = 0;
	std::cout << "\e[0;33mDefault Constructor called of RPN\e[0m" << std::endl;
}

RPN::RPN(const RPN &copy)
{
	_s = copy.getS();
	std::cout << "\e[0;33mCopy Constructor called of RPN\e[0m" << std::endl;
}

RPN::RPN(int argc, char *argv[])
{
	std::cout << "\e[0;33mFields Constructor called of RPN\e[0m" << std::endl;
}


// Destructor
RPN::~RPN()
{
	std::cout << "\e[0;31mDestructor called of RPN\e[0m" << std::endl;
}


// Operators
RPN & RPN::operator=(const RPN &assign)
{
	_s = assign.getS();
	return *this;
}


// Getters / Setters
std::stack<int> RPN::getS() const
{
	return _s;
}
