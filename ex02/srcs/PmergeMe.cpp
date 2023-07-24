/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:39:16 by alexanderva       #+#    #+#             */
/*   Updated: 2023/05/10 14:40:20 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

// Constructors
PmergeMe::PmergeMe()
{
	_vecInt.clear();
	_listInt.clear();
	if (DEBUGGING)
		std::cout << "\e[0;33mDefault Constructor called of PmergeMe\e[0m" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	_vecInt = copy.getVecInt();
	_listInt = copy.getListInt();
	if (DEBUGGING)
		std::cout << "\e[0;33mCopy Constructor called of PmergeMe\e[0m" << std::endl;
}

PmergeMe::PmergeMe(const int args, char **argv)
{
	if (DEBUGGING)
		std::cout << "\e[0;33mFields Constructor called of PmergeMe\e[0m" << std::endl;
	// Check for correct number of arguments
	if (args < 2)
		throw std::invalid_argument("Error: Please provide at least one integer argument.");
	parseVector(args, argv);
	parseList();
}

// Destructor
PmergeMe::~PmergeMe()
{
	if (DEBUGGING)
		std::cout << "\e[0;31mDestructor called of PmergeMe\e[0m" << std::endl;
}


// Operators
PmergeMe & PmergeMe::operator=(const PmergeMe &assign)
{
	_vecInt = assign.getVecInt();
	_listInt = assign.getListInt();
	return *this;
}

// Getters / Setters
std::vector<int> PmergeMe::getVecInt() const
{
	return _vecInt;
}
std::list<int> PmergeMe::getListInt() const
{
	return _listInt;
}

// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Parses integer arguments and stores them in a vector.
 * 
 * This function parses integer arguments from `argv` using an `istringstream`,
 * and stores the resulting integers in `_vecInt`.
 * 
 * @param args The number of arguments in `argv`.
 * @param argv An array of C-style strings representing the program's arguments.
 * 
 * @throws std::invalid_argument If `argv` contains a non-integer argument.
 */
void PmergeMe::parseVector(const int args, char **argv)
{
	// Parse integer arguments and store them in a vector
	for (int i = 1; i < args; ++i)
	{
		int value;
		std::istringstream streamValue(argv[i]);

		streamValue >> value;
		if (streamValue.fail() || value  < 0)
			throw std::invalid_argument("Error: Please provide a valid integer arguments.");
		_vecInt.push_back(value);
	}
}

/**
 * @brief Copies the elements from _vecInt to _listInt using std::copy and std::back_inserter.
 * 
 * This function uses std::copy to copy the elements from _vecInt to _listInt.
 * The std::back_inserter function is used to create an output iterator that
 * appends the copied elements to the end of _listInt.
 */
void PmergeMe::parseList(void)
{
	// Copy the vector elements to the list
	std::copy(_vecInt.begin(), _vecInt.end(), std::back_inserter(_listInt));
}