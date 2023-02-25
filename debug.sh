#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Usage: <executable>"
else
    valgrind --leak-check=full --show-leak-kinds=all "$1"
fi
