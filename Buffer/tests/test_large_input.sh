#!/bin/bash

echo "Medium file test:"
head -c 1024 /dev/urandom > medium_input.txt
./xd.c medium_input.txt
