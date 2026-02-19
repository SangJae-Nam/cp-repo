#!/bin/bash

set -e
 
# Check if the limit argument is provided
if [ "$#" != "1" ]; then
	echo "Usage $0 OPTIMIZED_FILE"
	exit 1
fi

OPTIMIZED_FILE=$1
TC_GEN_FILE=generate_tc.cpp
LIMIT=5000
 
# Compile the C++ files with g++ (version c++17)
set -x
g++ -std=c++17 -Wall $OPTIMIZED_FILE -o a
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
done
 
echo "All tests passed"
