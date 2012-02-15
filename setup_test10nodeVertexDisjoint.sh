#!/bin/bash
rm test1Vertex.txt
for (( i = 1 ; i <= 10 ; i++ ))
do
	for (( j = 1 ; j <= 10 ; j++  ))
	do
		if [ $i -ne $j ]
		then
			./vertex_disjoint 10node.txt $i $j >> test1Vertex.txt
		fi
	done
done

