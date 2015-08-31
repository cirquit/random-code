#! /bin/bash

# Declaring an array with 4 elements

ARRAY=( 'Debian Linux' 'Redhat Linux' Ubuntu Linux )

# get number of elements in the array

ELEMENTS=${#ARRAY[@]}

for (( i=0; i < $ELEMENTS; i++)); do
  echo ${ARRAY[${i}]}
done