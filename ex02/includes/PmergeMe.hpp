#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>

//colors
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

# define DEBUGGING 0

class PmergeMe
{
	public:
        // ─── Constructors ────────────────────────────────────────────
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe(const int args, char **argv);
		
        // ─── Destructor ──────────────────────────────────────────────
		~PmergeMe();

        // ─── Operators ───────────────────────────────────────────────
		PmergeMe & operator=(const PmergeMe &assign);
		
        // ─── Getters And Setters ─────────────────────────────────────
		std::vector<int> getVecInt() const;
		std::list<int> getListInt() const;

        // ─── Methods ─────────────────────────────────────────────────
		void parseVector(const int args, char **argv);
		void parseList(void);

		template <typename T>
		friend void mergeSort(typename T::iterator start, typename T::iterator end);
		template <typename T>
		friend void merge(typename T::iterator leftStart, typename T::iterator leftEnd,
				   typename T::iterator rightStart, typename T::iterator rightEnd);


	private:
        // ─── Private Attributes ──────────────────────────────────────
		std::vector<int> _vecInt;
		std::list<int> _listInt;
};

#endif