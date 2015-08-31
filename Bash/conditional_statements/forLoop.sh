#!/bin/bash

path=/home/rewrite/Documents

for f in $( ls $path ); do
  echo $f
done