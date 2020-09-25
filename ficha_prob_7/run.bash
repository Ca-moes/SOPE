#!/bin/bash
# $? = 0 se compilou bem
# $? = 2 otherwise
gcc -D_REENTRANT -pthread -lrt -Wall -o prog $@ 
if [ $? -eq 0 ] ; then
  ./prog 
  rm prog
else
  echo "COMPILATION ERROR";
fi
