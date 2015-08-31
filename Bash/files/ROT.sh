#!/bin/bash

## Global variables
encrypt="false"
decrypt="false"
shiftby=0
count=0
file=""
declare -a array

## Helper definition

# decimal value to ASCII character
chr(){
  printf \\$(printf '%03o' $1)
}

# ASCII character to decimal value
ord(){
  printf '%d' "'$1"
}

# Transforms every ASCII character with applied "shiftby" back to ASCII
map_over_string(){

  arg="$1"
  length=$((${#arg}-1))
  str=""

# check for double flags
  if [[ "$encrypt" == "true" && "$decrypt" == "true" ]]; then
    echo "You want to encrypt and decrypt at the same time..."
    exit 1

# encrypt adds 'shiftby' to ASCII value
  elif [[ "$encrypt" == "true" ]]; then
      for i in `seq 0 $length`; do
        cur_char=${arg:i}
        cur_char_ord=$(ord $cur_char)
        new_char_ord=`expr $cur_char_ord + $shiftby`
        new_char=$(chr $new_char_ord)
        str=$str$new_char
      done

# decrypts subtracts 'shiftby' to ASCII value
  elif [[ "$decrypt" == "true" ]]; then
      for i in `seq 0 $length`; do
        cur_char=${arg:i}
        cur_char_ord=$(ord $cur_char)
        new_char_ord=`expr $cur_char_ord - $shiftby`
        new_char=$(chr $new_char_ord)
        str=$str$new_char
      done

# check if an any flags are set
  else
      echo "You have to choose if you want to encrypt or decrypt..."
      exit 1
  fi
}

## Main entry point

while getopts 'eds:f:' flag; do
  case "${flag}" in
    e) encrypt="true" ;;
    d) decrypt="true" ;;
    f) file="${OPTARG}" ;;
    s) shiftby="${OPTARG}" ;;
    *) error "Unexpected option ${flag}" ;;
  esac
done

# check if file exists
if [[ ! -e $file ]]; then

    echo "$file does not exist, sorry :("

else

    exec<$file

    while read line; do
      map_over_string "$line"
      array[$count]="$str"
      count=`expr $count + 1`;
    done

    printf "%s\n" "${array[@]}"

fi