# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pmergeme_test_.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 10:10:01 by alexanderva       #+#    #+#              #
#    Updated: 2023/05/11 10:28:34 by alexanderva      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[33m'
END='\033[0m'
BOLD='\033[1m'

# Define the PmergeMe command
PmergeMe="./PmergeMe"

function test_empty_list {
  echo -e "${BOLD}===================================${END}"
  echo -e "Test: ${BOLD} ${RED}Empty List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe${END}"
  output=$($PmergeMe 2>&1)
  expected="Some error "
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_negative_list {
  echo -e "${BOLD}===================================${END}"
  echo -e "Test: ${BOLD} ${RED}Negative numbers${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe -1 -4 -5 33${END}"
  output=$($PmergeMe -1 -4 -5 33 2>&1)
  expected="Some error "
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_number_characters_list {
  echo -e "${BOLD}===================================${END}"
  echo -e "Test: ${BOLD} ${RED}number with character mixed at the end${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 555skdfj 1 2 3/// 7 9... 55${END}"
  output=$($PmergeMe 555skdfj 1 2 3/// 7 9... 55 2>&1)
  expected="Before: 555 1 2 3 7 9 55\nAfter: 1 2 3 7 9 55 555"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_single_element_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Single Element List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 1${END}"
  output=$($PmergeMe 1 2>&1)
  expected="Before: 1 \nAfter: 1"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_two_element_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Two Element List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 2 1${END}"
  output=$($PmergeMe 2 1 2>&1)
  expected="Before: 2 1\nAfter: 1 2"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_identical_elements_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Identical Elements List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 5 5 5 5 5${END}"
  output=$($PmergeMe 5 5 5 5 5 2>&1)
  expected="Before: 5 5 5 5 5\nAfter: 5 5 5 5 5"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_sorted_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Sorted List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 1 2 3 4 5${END}"
  output=$($PmergeMe 1 2 3 4 5 2>&1)
  expected="Before: 1 2 3 4 5\nAfter: 1 2 3 4 5"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_reverse_sorted_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Reverse Sorted List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 5 4 3 2 1${END}"
  output=$($PmergeMe 5 4 3 2 1 2>&1)
  expected="Before: 5 4 3 2 1\nAfter: 1 2 3 4 5"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

function test_duplicate_elements_list {
  echo -e "${BOLD}==================================="
  echo -e "Test: ${RED}Duplicate Elements List${END}"
  echo -e "${BOLD}===================================${END}"
  echo -e "${BOLD}${YELLOW}Test sent: ${END}${BOLD}PmergeMe 1 3 5 3 2 5${END}"
  output=$($PmergeMe 1 3 5 3 2 5 2>&1)
  expected="Before: 1 3 5 3 2 5\nAfter: 1 2 3 3 5 5"
  echo -e "${BOLD}${YELLOW}Expected:\n${END}${BOLD}$expected${END}"
  echo -e "${BOLD}${YELLOW}Got:\n${END}${BOLD}$output${END}"
}

# Call test functions
test_empty_list
test_negative_list
test_number_characters_list
test_single_element_list
test_two_element_list
test_identical_elements_list
test_sorted_list
test_reverse_sorted_list
test_duplicate_elements_list