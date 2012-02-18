#!/bin/bash
rm testAllEdge.txt


for (( i = 1 ; i <= 75 ; i++ ))
do
	for (( j = 1 ; j <= 75 ; j++  ))
	do
		#if [ $i -ne $j ]
		#then
			./edge_disjoint 75node.txt $i $j >> testAllEdge.txt
		#fi
	done
done

