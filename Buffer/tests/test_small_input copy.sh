#!/bin/bash

echo "Large file test:"
head -c 1048576 /dev/urandom > large_input.txt
./xd.c large_input.txt
