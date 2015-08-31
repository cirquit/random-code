#!/bin/bash

## -| split Arguments by something else than spaces
#  -- with the (I)nternal (F)ield (S)eperator


# save the old IFS-value
old_IFS="$IFS"

# set the new IFS to ':'
IFS=":"

echo -n "Please input 3 arguments seperated by ':' "

read x y z

echo "First argument is: $x"
echo "Second argument is: $y"
echo "Third argument is: $z"

# don't forget to set it back
IFS=$old_IFS