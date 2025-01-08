#!/bin/bash

echo "Delayed input test:"
./delayinput.sh large_input.txt | ./xd.c -
