#! /bin/bash
# how to access starting arguments

echo $1 $2 $3 ' -> echo $1 $2 $3'

# how to store arguments in an array

args=("$@")

echo ${args[0]} ${args[1]} ${args[2]} ' -> args=("$@"); echo ${args[0]} ${args[0]} ${args[0]} '

# how to print all arguments at once

echo $@ ' -> echo $@'

# how to get the number of arguments

echo Numbers of arguements passed: $# ' -> echo Numbers of arguments passed: $#'