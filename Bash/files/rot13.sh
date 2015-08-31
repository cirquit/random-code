#!/bin/bash

rot13(){
  tr "[a-m][n-z][A-M][N-Z]" "[n-z][a-m][N-Z][A-M]"
}

cat "$@" | rot13