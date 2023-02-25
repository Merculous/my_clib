#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Usage: <file>.c"
else
    gcc -Wall -Werror -Wextra "$1"
fi
