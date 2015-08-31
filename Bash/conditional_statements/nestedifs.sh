#! /bin/bash

# Declare variable choice and assign value 4

choice=4

# Print choices

start (){
  echo "1. Bash"
  echo "2. Scripting"
  echo "3. Tutorial"
  echo -n "Please choose a word [1,2 or 3]?"
}

start

# Loop while the var choice is equal 4

while [ $choice -eq 4 ]; do

read choice


## -| Testing nested ifs the new way

    if [[ $choice -eq 1 ]]; then
        echo "You have chosen the word: Bash!"
    elif [[ $choice -eq 2 ]]; then
        echo "You have chosen the word: Scripting!"
    elif [[ $choice -eq 3 ]]; then
        echo "You have chosen the word: Tutorial!"
    else
        echo "Please make a choice between 1-3!"
        start
        choice=4
    fi


## -| Testing nested if's the old way

#    if [ $choice -eq 1 ];
#    then
#        echo "You have chosen word: Bash!"
#    else
#        if [ $choice -eq 2 ];
#        then
#            echo "You have chosen word: Scripting!"
#        else
#            if [ $choice -eq 3 ];
#            then
#                echo "You have chosen word: Tutorial!"
#            else
#                echo "Please make a choice between 1-3!"
#                start
#                choice=4
#            fi
#        fi
#    fi

done