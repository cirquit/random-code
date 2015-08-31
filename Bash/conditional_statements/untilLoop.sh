#!/bin/bash

COUNT=0

until [[ $COUNT -gt 5 ]]; do

    echo "Value of count is: $COUNT"

    # let COUNT= COUNT+1
    #or
    COUNT=$(($COUNT+1))

done