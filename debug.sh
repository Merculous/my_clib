#!/bin/sh

valgrind --leak-check=full --show-leak-kinds=all -s "./build/MY_CLIB" "$@"
