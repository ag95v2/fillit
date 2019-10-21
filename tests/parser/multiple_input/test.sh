#!/bin/bash

for FILE in $(ls bad*.txt) 
do 
	echo $FILE
	./test_parser $FILE
done
