/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:57 by alexanderva       #+#    #+#             */
/*   Updated: 2023/05/14 13:44:10 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

#define ERROR_NUM_ARG "The argument number provided should be greater \
than 0 and lower or equal to 10" 

const int MAX_OPERANDS = 2; // Maximum number of operands for an operator
const int MAX_RESULT = 1e9; // Maximum result value

bool is_operator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "**"; // Check if token is an operator
}

bool is_number(const std::string &token)
{
    char *endptr;
    std::strtod(token.c_str(), &endptr); // Convert token to double
    return *endptr == '\0';              // Check if conversion was successful
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {                                                              // Check if there is at least one command line argument
        std::cout << argc << std::endl;
        std::cout << "Error: insufficient arguments" << std::endl; // Print error message
        return 1;                                                  // Exit with error code
    }

    std::string expression = argv[1]; // Get expression string from command line argument
    std::stringstream ss(expression); // Initialize stringstream with expression string
    std::string token;                // Initialize token string
    std::stack<double> s;             // Initialize stack for numbers

    while (ss >> token)
    { // Iterate through each token in the expression
        // std::cout << token << std::endl;
        if (!is_operator(token) && !is_number(token))
        {                                                                       // Check if token is a valid operator or number
            std::cout << "Error: invalid token '" << token << "'" << std::endl; // Print error message
            return 1;                                                           // Exit with error code
        }
        if (is_number(token))
        {                                                     // If token is a number
            double num = std::strtod(token.c_str(), nullptr); // Convert token to double
            try
            {
                if (num < 0 || num > 10)
                    throw std::invalid_argument(ERROR_NUM_ARG);
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
                return -1;
            }
            
            s.push(num);                                      // Push number onto stack
        }
        else
        { // If token is an operator
            if (s.size() < MAX_OPERANDS)
            {                                                                                            // Check if there are enough operands on the stack
                std::cout << "Error: insufficient operands for operator '" << token << "'" << std::endl; // Print error message
                return 1;                                                                                // Exit with error code
            }
            double b = s.top();
            s.pop(); // Pop top two numbers from stack
            double a = s.top();
            s.pop();
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
                {                                                        // Check for division by zero
                    std::cout << "Error: division by zero" << std::endl; // Print error message
                    return 1;                                            // Exit with error code
                }
                result = a / b;
            }
            else if (token == "**")
            { // Perform exponentiation
                result = std::pow(a, b);
            }
            if (std::abs(result) > MAX_RESULT)
            {                                                        // Check if result is too large
                std::cout << "Error: result too large" << std::endl; // Print error message
                return 1;                                            // Exit with error code
            }
            s.push(result); // Push result onto stack
        }
    }

    if (s.size() != 1)
    {                                                         // Check if there is only one number on the stack
        std::cout << "Error: too many operands" << std::endl; // Print error message
        return 1;                                             // Exit with error code
    }

    std::cout << s.top() << std::endl; // Display result to user

    return 0; // Exit with success code
}
