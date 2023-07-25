/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2023/04/25 17:41:33 by alexanderva       #+#    #+#             */ /*   Updated: 2023/07/12 15:52:40 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//! ─────────────────────────────────────────────────────────────────────────────

// Constructors
BitcoinExchange::BitcoinExchange()
{
	_dataMap.clear();
	std::cout << "\e[0;33mDefault Constructor called of BitcoinExchange\e[0m" << std::endl;
    std::cout << BOLD << "-----------------------------------------------\n" << END;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	_dataMap = copy.getDataMap();
	std::cout << "\e[0;33mCopy Constructor called of BitcoinExchange\e[0m" << std::endl;
}

// Destructor
BitcoinExchange::~BitcoinExchange()
{
    std::cout << BOLD << "-----------------------------------------------\n" << END;
	std::cout << "\e[0;31mDestructor called of BitcoinExchange\e[0m" << std::endl;
}


// Operators
BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &assign)
{
	_dataMap = assign.getDataMap();
	return *this;
}


// Getters / Setters
std::map<std::string, double> BitcoinExchange::getDataMap() const
{
	return _dataMap;
}
//! ─────────────────────────────────────────────────────────────────────────────


//? This function reads an input file line by line and processes each line
void BitcoinExchange::processInputFile(std::ifstream &inputFile)
{
    std::string line;
    std::getline(inputFile, line); // Ignore header line

    while (std::getline(inputFile, line))
    {
        try
        {
            processLine(line);
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << '\n';
            break;
        }
    }
}

//? This function processes a single line from the input file
void BitcoinExchange::processLine(const std::string &line)
{

    // Create an input string stream for the given line
    std::istringstream iss(line);

    // Initialize variables for the date, value string, and value in USD
    std::string date, valueStr;
    double value;

    // Parse the date and value from the input line using the '|' separator
    std::getline(iss, date, '|');
    std::getline(iss, valueStr);

    //Erase spaces
    //! std::remove_if move characters that meet the condition to the end of the string and return the fist character that 
    //! met condition list
    //? erase by the other side specified in the interator list provided in the function

    date.erase(std::remove_if(date.begin(), date.end(), ::isspace), date.end());

    // Check if the date is valid
    if (!isValidDate(date))
    {
        // If the date is not valid, print an error message and return
        std::cerr << BOLD << RED << "Error: " << END << BOLD << "not a valid date => " 
        << YELLOW << date << END << std::endl;
        return;
    }

    // Check if the value is valid (i.e., a positive number)
    if (!isValidValue(valueStr))
    {
        // If the value is not valid, print an error message and return
        std::cerr << BOLD << RED << "Error:" << END << BOLD << " not a valid number. => " 
        << YELLOW << valueStr << END <<std::endl;
        return;
    }

    // Convert valueStr to input stream
    std::istringstream ss(valueStr);

    // Convert the value from string to double
    ss >> value;

    // Look up the exchange rate for the given date
    double exchangeRate = findExchangeRate(date);
    // If give date doesn't match
    if (exchangeRate < 0)
    {
        // the lower_boud function search for a value greater or equal to the key passed
        // if not found it returns the next one greater than the value searched 
        std::map<std::string, double>::iterator it = _dataMap.lower_bound(date);
        if (it != _dataMap.begin())
        {
            it--; 
            exchangeRate = it->second;
            date = it->first;
        }
        else
        {
            std::cerr << BOLD << RED << "Error: " << END << BOLD << " no date found => " 
            << YELLOW << date << END << std::endl;
            return ;
        }
    }
    // Calculate the result (i.e., the value converted to USD)
    long double result = value * exchangeRate;
    // Print the result to the console
    std::cout << BOLD << date << " => " << value << " = " << GREEN 
    << std::setprecision(15) << result << END << std::endl;
}

//? This function checks if a given date string is valid
bool BitcoinExchange::isValidDate(const std::string &date)
{
    int year, month, day;
    char sep, sep1;

    std::istringstream iss(date);
    iss >> year >> sep >> month >> sep1 >> day;

    if (iss.fail() || sep != '-' || sep1 != '-')
        return false;

    if (year < 1900 || year > 2100)
        return false;

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    // information extracted from Wikipedia https://en.wikipedia.org/wiki/Leap_year
    if (year % 4 == 0 && (year % 100 == 0 || year % 400 != 0))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])// checks months days within the int array
        return false;

    return true;
}

//? This function checks if a given value string is valid (i.e., a positive number)
bool BitcoinExchange::isValidValue(const std::string &value)
{
    std::istringstream iss(value);
    double doubleValue;

    if (!(iss >> doubleValue))
    {
        return false;
    }

    if (doubleValue <= 0.0 || doubleValue > 1000.0)
    {
        return false;
    }

    return true;
}

//? This function looks up the exchange rate for a given date
double BitcoinExchange::findExchangeRate(const std::string &date)
{
    double exchangeRate = -1.0; // Default value if date not found
    std::map<std::string, double>::iterator it;

    parseDataBase();
    it = _dataMap.find(date);
    if (it != _dataMap.end())
        exchangeRate = _dataMap[date];
    return exchangeRate;
}

/**
    @brief Parses a CSV file containing Bitcoin exchange rates and stores them in a map
    @details This function opens the CSV file located at "./data_base/data.csv" and reads each line.
    Each line contains a date and a corresponding exchange rate value, separated by a comma. The function
    then stores each date and exchange rate value in a map named _dataMap, with the date as the key and
    the exchange rate as the value. If the file fails to open, a runtime error is thrown.
    @param void
    @return void
*/
void BitcoinExchange::parseDataBase(void)
{
    std::ifstream file("./data_base/data.csv");

    if (file)
    {
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line))
        {
            std::istringstream iss(line); // inputString representing the line
            std::string dateToken;
            std::string valueToken;
            std::getline(iss, dateToken, ',');  // Get date token
            std::getline(iss, valueToken, ','); // Get exchange rate token
            std::istringstream vss(valueToken); // Convert valueToken to input stream
            double exchangeRate;
            vss >> exchangeRate;                // Convert token input stream to double
            _dataMap[dateToken] = exchangeRate; // stores each element in a map
        }
    }
    else
    {
        throw std::runtime_error("Error: could not open data.csv");
    }
}