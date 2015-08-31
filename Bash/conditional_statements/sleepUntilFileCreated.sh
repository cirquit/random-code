#!/bin/bash

file="./myFile.hs"

while [ ! -e $file ]; do
  sleep 1
done