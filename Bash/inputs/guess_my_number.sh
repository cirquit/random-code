#!/bin/bash

## -| popular guess my number game

to_guess=$((RANDOM%10+1))

guessed=11

echo "Guess a number between 1 and 10 (it's $to_guess)"

while [[ ! guessed -eq to_guess ]]; do

  echo -n "Type here: "
  read guessed

  if [[ guessed -eq to_guess ]]; then
    echo "You guessed right!"
  elif [[ guessed -lt to_guess ]]; then
    echo "Your guess is lower!"
  elif [[ guessed -gt to_guess ]]; then
    echo "Your guess is greater!"
  fi

done
