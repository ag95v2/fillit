#!/bin/sh

echo "Running time test for generic swap"
time ./normal_swap
echo "\n\nRunning time test for explicit integer swap"
time ./int_swap
