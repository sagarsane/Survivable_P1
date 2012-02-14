#!/bin/bash
rm test2Edge.txt

for (( i = 1 ; i <= 75 ; i++ ))
do
#	for (( j = 1 ; j <= 10 ; j++  ))
#	do
		if [ $i -ne 7 ]
		then
			./edge_disjoint 75node.txt 7 $i >> test2Edge.txt
		fi
#	done
done

