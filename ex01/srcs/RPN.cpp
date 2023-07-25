#include "RPN.hpp"

// Constructors
RPN::RPN()
{
	if (PRINTING)
		std::cout << "\e[0;33mDefault Constructor called of RPN\e[0m" << std::endl;
}

RPN::RPN(const RPN &copy)
{
	_s = copy.getS();
	if (PRINTING)
		std::cout << "\e[0;33mCopy Constructor called of RPN\e[0m" << std::endl;
}

RPN::RPN(std::stringstream &ss)
{
	if (PRINTING)
		std::cout << "\e[0;33mFields Constructor called of RPN\e[0m" << std::endl;

	_s.empty();

	std::string token; // Initialize token string

	while (ss >> token)
	{ // Iterate through each token in the expression
		// std::cout << token << std::endl;
		if (!is_operator(token) && !is_number(token))
			throw std::invalid_argument("Error: invalid token '" + token + "'"); // Check if token is a valid operator or number
		if (is_number(token))
		{										   // If token is a number
			std::stringstream streamNumber(token); // convert number token to stringStream
			double num;

			streamNumber >> num; // Convert token to double
			if (num < 0 || num > 10)
				throw std::invalid_argument(ERROR_NUM_ARG);

			_s.push(num); // Push number onto stack
		}
		else
		{ // If token is an operator
			addOperator(token);
		}
	}
	if (_s.size() != 1)
		throw std::invalid_argument("Error: too many operands"); // Check if there is only one number on the stack
	std::cout << _s.top() << std::endl;							 // Display result to user
}

 RPN::~RPN()
{
	if (PRINTING)
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

// Methods
bool RPN::is_operator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" ; // Check if token is an operator
}

bool RPN::is_number(const std::string &token) 
{
    char *endptr;
    std::strtod(token.c_str(), &endptr); // Convert token to double
    return *endptr == '\0';              // Check if conversion was successful
}

void RPN::addOperator(std::string token)
{
	if (_s.size() < MAX_OPERANDS)
		throw std::invalid_argument("Error: insufficient operands for operator '" + token + "'"); // Check if there are enough operands on the stack
	double b = _s.top();
	_s.pop(); // Pop top two numbers from stack
	double a = _s.top();
	_s.pop();
	double result;
	if (token == "+")
	{ // Perform addition
		result = a + b;
	}
	else if (token == "-")
	{ // Perform subtraction
		result = a - b;
	}
	else if (token == "*")
	{ // Perform multiplication
		result = a * b;
	}
	else if (token == "/")
	{ // Perform division
		if (b == 0)
			throw std::invalid_argument("Error: division by zero"); // Check for division by zero
		result = a / b;
	}
	if (std::abs(result) > MAX_RESULT)
		throw std::invalid_argument("Error: result too large"); // Check if result is too large
	_s.push(result);
}