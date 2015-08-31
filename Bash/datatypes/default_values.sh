#!/bin/bash

## -| default values

echo -n "Please input your name, or don't = "

read name

echo "Your name is ${name:=Steve Words}"