/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:33:09 by alexanderva       #+#    #+#             */
/*   Updated: 2023/04/26 10:17:27 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

// ─── Color ─────────────────────────────────────────────────────────────────
# define RESET	"\033[0;0m"
# define ERASE	"\033[2K\r"
# define GREY	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define BOLD	"\033[1m"
# define UNDER	"\033[4m"
# define SUR	"\033[7m"
# define END	"\033[0m"
# define CENTER	"\033[60G"

class BitcoinExchange
{
	public:
		// Constructors
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		
		// Destructor
		~BitcoinExchange();
		
		// Operators
		BitcoinExchange & operator=(const BitcoinExchange &assign);
		
		// Getters / Setters
		std::map<std::string, double> getDataMap() const;

        //methods
        void processInputFile(std::ifstream &inputFile);

    private:
        //attributes
		std::map<std::string, double> _dataMap;

        //methods
        void processLine(const std::string &line);
        bool isValidDate(const std::string &date);
        bool isValidValue(const std::string &value);
        double findExchangeRate(const std::string &date);
        void parseDataBase(void);
};

#endif