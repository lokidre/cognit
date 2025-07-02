#! /bin/bash

file=$1

./histogram $file
./histogram-equ-research $file
./histogram ${file%.*}-equ.${file##*.}

