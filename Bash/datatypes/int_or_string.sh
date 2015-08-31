#!/bin/bash

## -| how to check if the input is an integer or string

echo -en "Please guess the magic number! "
read number

# (1) grep gets matches against everything that is not [0..9]
# (2) if it finds anything, its exit code is '0' for success
# (3) any (error-)output is redirecet to the null device

#              (1) && (2)    (3)
echo $number | grep [^0-9] > /dev/null 2>&1

#       (2)
if [[ $? -eq 0 ]]; then
  echo "This is not a number, sorry!"
elif [[ $number -eq 7 ]]; then
  echo "You got it right!"
else
  echo "Sorry, wrong number!"
fi

