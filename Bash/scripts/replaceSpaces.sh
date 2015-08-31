#!/bin/bash

# This bash script will locate and replace spaces in filenames

DIR="."

find $DIR -type f | while read file; do

# using POSIX class [:space:] to find space in the filename

    if [[ "$file" = *[[:space:]]* ]];
        then
            mv "$file" `echo $file | tr ' ' '_'`
            echo "$file renamed"
    fi
done