/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:15:00 by alexanderva       #+#    #+#             */
/*   Updated: 2023/07/25 09:26:17 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
// Print any data structure
template <typename T>
void printDataStructure(const T &dataStructure)
{
    typename T::const_iterator iter;
    for (iter = dataStructure.begin(); iter != dataStructure.end(); ++iter)
        std::cout << BOLD << *iter << END <<" ";
    std::cout << std::endl;
}

// ─── Template Methods ────────────────────────────────────────
template <typename T>
void merge(typename T::iterator leftStart, typename T::iterator leftEnd,
           typename T::iterator rightStart, typename T::iterator rightEnd)
{
    T merged;
    typename T::iterator leftIt = leftStart;
    typename T::iterator rightIt = rightStart;
    while (leftIt != leftEnd && rightIt != rightEnd)
    {
        if (*leftIt <= *rightIt)
        {
            merged.push_back(*leftIt);
            ++leftIt;
        }
        else
        {
            merged.push_back(*rightIt);
            ++rightIt;
        }
    }
    while (leftIt != leftEnd)
    {
        merged.push_back(*leftIt);
        ++leftIt;
    }
    while (rightIt != rightEnd)
    {
        merged.push_back(*rightIt);
        ++rightIt;
    }
    typename T::iterator mergedIt = merged.begin();
    for (typename T::iterator it = leftStart; it != rightEnd; ++it)
    {
        *it = *mergedIt;
        ++mergedIt;
    }
}

template <typename T>
void mergeSort(typename T::iterator start, typename T::iterator end)
{
    if (start == end || std::distance(start, end) == 1)
        return;
    typename T::iterator mid = start;
    std::advance(mid, std::distance(start, end) / 2);
    mergeSort<T>(start, mid);
    mergeSort<T>(mid, end);
    merge<T>(start, mid, mid, end);
}

// ─────────────────────────────────────────────────────────────────────────────


int main(int argc, char *argv[])
{

    PmergeMe object;
    try
    {
        //checks args errors, parse argv and initialize vector
        object = PmergeMe(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    std::vector<int> vecTemp = object.getVecInt();
    std::list<int> listTemp = object.getListInt();

    // Print unsorted sequence
    std::cout  << BOLD << RED << "Before: " << END;
    printDataStructure<std::vector<int> >(vecTemp);
    std::cout << std::endl << std::endl;

    // Sort vector sequence using merge-insert sort
    clock_t start = clock();
    mergeSort<std::vector<int> >(vecTemp.begin(), vecTemp.end());
    clock_t end = clock();
    long double time_taken = (long double)(end - start) / (long double)(CLOCKS_PER_SEC);

    // Print sorted vector sequence
    std::cout  << BOLD << GREEN << "After: " << END; 
    printDataStructure<std::vector<int> >(vecTemp);
    std::cout << std::endl;

    // Print time taken by merge-insert sort
    std::cout << "Time to process a range of " << vecTemp.size() << " with std::vector<int>: ";
    std::cout << std::fixed << std::setprecision(10) << time_taken << " s" << std::endl;

    start = clock();
    mergeSort<std::list<int> >(listTemp.begin(), listTemp.end());
    end = clock();
    time_taken = (long double)(end - start) / (long double)(CLOCKS_PER_SEC);

    // Print time taken by second container to sort
    std::cout << "Time to process a range of " << listTemp.size() << " with std::list<int>";
    std::cout << std::fixed << std::setprecision(10) << time_taken << " s" << std::endl;

    return 0;
}