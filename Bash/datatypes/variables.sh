#! /bin/bash
# Global variables

VAR="global variable"

function print_local {

  local VAR="local variable"
  echo $VAR
}

echo $VAR

print_local

echo $VAR