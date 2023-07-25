#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

#define ERROR_NUM_ARG "The argument number provided should be greater \
than 0 and lower or equal to 10" 
#define MAX_OPERANDS  2 // Maximum number of operands for an operator
#define MAX_RESULT  1e9 // Maximum result value
#define PRINTING  0

class RPN
{
	public:
		// Constructors
		RPN();
		RPN(const RPN &copy);
		RPN(std::stringstream &ss);

		// Destructor
		~RPN();

		// Operators
		RPN &operator=(const RPN &assign);

		// Getters / Setters
		std::stack<int> getS() const;

		// Methods
		bool is_operator(const std::string &token);
		bool is_number(const std::string &token);
		void addOperator(std::string token);

	private:
		std::stack<int> _s;
};

#endif