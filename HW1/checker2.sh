#!/bin/bash

for file in data2/*.in
do
	time make -s run2 < $file > out && diff out `sed -e s/in$/out/ <<< $file`
done
