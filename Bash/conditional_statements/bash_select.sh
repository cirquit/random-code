#!/bin/bash
 
PS3="Choose one word: "

#bash select

select word in "linux" "bash" "scripting" "tutorial"
do
    echo "The word you have selected is $word"
    break
done

#exit 0

