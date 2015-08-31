#! /bin/bash

# Declare ARRAY

declare -a ARRAY

# Link filedescriptor 10 with stdin

exec 10<&0

# stdin replaced with a file supplied as a first argument

exec < $1

let count=0

while read LINE; do

  ARRAY[$count]=$LINE
  ((count++))

done

echo Numbers of elements: ${#ARRAY[@]}

# echo array content

echo ${ARRAY[@]}

# restore stdin from filedescriptor 10
# close filedescriptor 10
exec 0<&10 10<&-