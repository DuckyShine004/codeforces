#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: <filename>"
    exit 1
fi

FILENAME="$1.cpp"

make SRC=$FILENAME

if [ $? -eq 0 ]; then
    time ./$(basename "$1") <cp.in >cp.out
    cat cp.out
else
    echo "Compilation failed."
fi
