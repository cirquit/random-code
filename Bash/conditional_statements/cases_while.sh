#!/bin/bash

## -| never ending while

#while :
#  do
#    echo "Please type something - Ctrl-C to quit"
#    read INPUT
#    echo "You typed: $INPUT"
#done

## -| ending while with pre-set text

INPUT=""

while [[ $INPUT != "bye" ]]; do
  echo "Please type something - bye to quit"
  read INPUT
  echo "You typed: $INPUT"
done


## -| case with input from the prompt

#echo "What is your preferred programming / scripting language?"
#echo "1) bash"
#echo "2) perl"
#echo "3) haskell"
#echo "4) phyton"
#echo "5) c"
#echo "6) I don't know!"
#
#read input;
#
#case $input in
#    1) echo "You selected bash";;
#    2) echo "You selected perl!";;
#    3) echo "You selected haskell!";;
#    4) echo "You selected phyton!";;
#    5) echo "You selected c!";;
#    6) exit
#esac

## -| case while reading from a file

#while read f; do
#
#  case $f in
#    "hello")     echo "English"    ;;
#    "howdy")     echo "American"   ;;
#    "gday")      echo "Australian" ;;
#    "bonjour")   echo "French"     ;;
#    "guten tag") echo "German"     ;;
#    *)           echo "Unknown language: $f" ;;
#  esac
#done < myfile.txt