#!/bin/bash

set -ex

SRC=$1
INFILE=$2
OUTFILE=$3

if [ "${INFILE}" != "" ]; then
	IN_OPT=" < ${INFILE}"
fi

if [ "${OUTFILE}" != "" ]; then
	OUT_OPT=" > ${OUTFILE}"
fi

g++ $1 -g -Wall -std=c++17

./a.out ${IN_OPT} ${OUT_OPT}
