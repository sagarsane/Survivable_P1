#!/bin/bash
rm testAllVertex.txt

for (( i = 1 ; i <= 75 ; i++ ))
do
	for (( j = 1 ; j <= 75 ; j++  ))
	do
		#if [ $i -ne $j ]
		#then
			./vertex_disjoint 75node.txt $i $j >> testAllVertex.txt
		#fi
	done
done

