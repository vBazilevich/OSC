#!/bin/bash

gcc -o ex2 ex2.c

cat /proc/cpuinfo | ./ex2 ex2.txt
