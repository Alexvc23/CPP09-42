#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

class RPN
{
	public:
		// Constructors
		RPN();
		RPN(const RPN &copy);
		RPN(int argc, char *argv[]);
		
		// Destructor
		~RPN();
		
		// Operators
		RPN & operator=(const RPN &assign);
		
		// Getters / Setters
		std::stack<int> getS() const;
		
	private:
		std::stack<int> _s;
		
};

#endif