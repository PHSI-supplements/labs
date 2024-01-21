#!/bin/sh

for i in 1 2 4 8 16
    do for j in {1..5}
        do
            ./mergesort input.txt 30000 $i > /dev/null
        done
    done
