#!/bin/bash
for i in {100..200}
do
	python3 lottery.py -l 100:100,100:100 -c -s $i -q 30 | awk '{if ($1 == "-->") {print $0;exit;}}'
done
