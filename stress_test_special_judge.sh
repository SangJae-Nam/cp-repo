#!/bin/bash

set -e
 
# Check if the limit argument is provided
if [ "$#" != "1" ]; then
	echo "Usage $0 SOURCE_FILE"
	exit 1
fi

SOURCE_FILE=$1
JUDGE_FILE=judge_tc.cpp
TC_GEN_FILE=generate_tc.cpp
LIMIT=10000
 
# Compile the C++ files with g++ (version c++17)
set -x
g++ -std=c++17 -Wall $SOURCE_FILE -o a
g++ -std=c++17 -Wall $TC_GEN_FILE -o gen
g++ -std=c++17 -Wall $JUDGE_FILE -o judge
set +x

# Run the loop for at most 'limit' number of times
for ((i=1; i<=LIMIT; i++))
do
  echo $i
  # Generate input using 'gen' binary
  ./gen > input.txt
 
  # Generate output using 'a' binary
  set +e
  ./a < input.txt > output_a.txt
  if [ $? -ne 0 ]; then
    echo "Runtime error in 'a' on iteration $i"
	echo "INPUT"
	cat input.txt
	echo
	echo
	echo "YOUR ANSWER"
	cat output_a.txt
	echo
	echo
    exit 1
  fi

  # Special case
  if [ "$(cat output_a.txt)" == "-1" ]; then
    echo "-1 Case on iteration $i"
	echo "INPUT"
	cat input.txt
	echo
	echo
    continue
  fi

  # Judge
  cp input.txt input_2.txt
  echo >> input_2.txt
  cat output_a.txt >> input_2.txt
  ./judge < input_2.txt
  if [ $? -ne 0 ]; then
    echo "Judge error in 'a' on iteration $i"
	echo "INPUT"
	cat input.txt
	echo
	echo
	echo "YOUR ANSWER"
	cat output_a.txt
	echo
	echo
    exit 1
  fi
done
 
echo "All tests passed"
