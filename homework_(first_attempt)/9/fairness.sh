#!/bin/bash
for i in {0..100}
do
	python3 lottery.py -l 100:100,100:100 -c -s $i | awk '{if ($1 == "-->") {print $0;exit;}}'
done
