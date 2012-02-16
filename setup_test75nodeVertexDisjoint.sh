#!/bin/bash
rm test2Vertex.txt
#$n = 1
for (( i = 1 ; i <= 75 ; i++ ))
do
#	for (( j = 1 ; j <= 10 ; j++  ))
#	do
		if [ $i -ne 7 ]
		then
			./vertex_disjoint 75node.txt 7 $i >> test2Vertex.txt
		fi
#	done
done

