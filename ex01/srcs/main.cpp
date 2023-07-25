/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:57 by alexanderva       #+#    #+#             */
/*   Updated: 2023/07/24 15:27:23 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    { // Check if there is at least one command line argument
        std::cout << argc << std::endl;
        std::cout << "Error: insufficient arguments" << std::endl; // Print error message
        return 1;                                                  // Exit with error code
    }

    std::string expression = argv[1]; // Get expression string from command line argument
    std::stringstream ss(expression); // Initialize stringstream with expression string

    try
    {
        RPN object(ss);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0; // Exit with success code
}
