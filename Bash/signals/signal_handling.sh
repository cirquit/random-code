#! /bin/bash

# bash trap command

trap bashtrap INT

# bash clear screen command (does so without newline)

clear;

# bash clear screen command (does so with newline)

# echo `clear`

# bash trap function is executed when SIGINT / CTRL-C is pressed
# bash prints message => Executing bash trap subrutine!

bashtrap() {
  echo "CTRL-C detected!...exectuing bash trap!"
}

for a in `seq 1 10`; do
    echo "$a/10 to exit."
    sleep 1;
done

echo "Exit bash trap example!"