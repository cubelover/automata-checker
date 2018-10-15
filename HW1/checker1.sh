#!/bin/bash

g++ -O2 -o checker1 checker1.cpp &&
for file in data1/*.in
do
	time make -s run1 < $file > out && ./checker1 "" out `sed -e s/in$/out/ <<< $file`
done
