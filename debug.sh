#!/bin/sh

valgrind --leak-check=full --show-leak-kinds=all -s ./tool kernelcache.encrypted
