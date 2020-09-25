#!/bin/bash
# USAGE ./run.bash p01a arg1 arg2
FILENAME=$1
CODEFILENAME="${FILENAME}.c"

rm $FILENAME -f
clear
echo $FILENAME

if gcc -Wall -o $FILENAME $CODEFILENAME; then 
./$FILENAME . names
else 
echo "COMPILATION ERROR";
fi 

# apaga todos os binarios criados por gcc
find . -type f  ! -name "*.*"  -delete
