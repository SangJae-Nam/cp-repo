#!/bin/bash

set -e
 
# Check if the limit argument is provided
if [ "$#" != "2" ]; then
	echo "Usage $0 OPTIMIZED_FILE BRUTE_FORCE_FILE"
	exit 1
fi

OPTIMIZED_FILE=$1
BRUTE_FORCE_FILE=$2
TC_GEN_FILE=generate_tc.cpp
LIMIT=5000
 
# Compile the C++ files with g++ (version c++17)
set -x
g++ -std=c++17 -Wall $OPTIMIZED_FILE -o a
g++ -std=c++17 -Wall $BRUTE_FORCE_FILE -o b
g++ -std=c++17 -Wall $TC_GEN_FILE -o gen
set +x

# Run the loop for at most 'limit' number of times
for ((i=1; i<=LIMIT; i++))
do
  echo $i
  # Generate input using 'gen' binary
  ./gen > input.txt
 
  # Generate output using 'a' binary
  ./a < input.txt > output_a.txt
  if [ $? -ne 0 ]; then
    echo "Runtime error in 'a' on iteration $i"
    exit 1
  fi
 
  # Generate output using 'b' binary
  ./b < input.txt > output_b.txt
  if [ $? -ne 0 ]; then
    echo "Runtime error in 'b' on iteration $i"
    exit 1
  fi
 
  # Compare the two output files
  if ! cmp -s output_a.txt output_b.txt; then
    echo "Mismatch found on iteration $i"
	echo "INPUT"
	cat input.txt
	echo
	echo
	echo "YOUR ANSWER"
	cat output_a.txt
	echo
	echo
	echo "CORRECT ANSWER"
	cat output_b.txt
	echo
    exit 1
  fi
done
 
echo "All tests passed"
