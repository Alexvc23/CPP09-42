#!/bin/bash

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Define test cases
TEST_CASES=(
    "2 3 +" "5"
    "4 2 -" "2"
    "3 5 *" "15"
    "6 2 /" "3"
    "2 +" "Error: insufficient operands for operator '+'"
    "+ 2 3" "Error: insufficient operands for operator '+'"
    "2 0 /" "Error: division by zero"
    "1 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +" "21"
    "1 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 -" "-19"
    "1 1 1 + +" "3" # additional tests
    "2 2 2 * *" "8"
    "3 3 /" "1"
    "100 10 /" "The argument number provided should be greater than 0 and lower or equal to 10"
    "/" "Error: insufficient operands for operator '/'"
    "*" "Error: insufficient operands for operator '*'"
    "-" "Error: insufficient operands for operator '-'"
    "+" "Error: insufficient operands for operator '+'"
    "5 0 *" "0"
    "5 1 -" "4"
    "100 50 -" "The argument number provided should be greater than 0 and lower or equal to 10"
)

# Loop through test cases
for (( i=0; i<${#TEST_CASES[@]}; i+=2 )); do
  input="${TEST_CASES[i]}"
  expected="${TEST_CASES[i+1]}"
  output=$(./RPN "$input" 2>&1)
  if [[ "$output" == "$expected" ]]; then
    echo -e "${GREEN}PASS: ${NC}$input = $expected${NC}"
  else
    echo -e "${RED}FAIL: $input = $output (expected $expected)${NC}"
  fi
done