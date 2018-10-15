#!/bin/bash

g++ -O2 -o checker checker.cpp &&
for file in data1/*.in
do
	time make -s run1 < $file > out && ./checker "" out `sed -e s/in$/out/ <<< $file`
done
