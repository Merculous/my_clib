#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Usage: <img3>"
else
    strings "$1" | grep -f "tags.txt"
fi
