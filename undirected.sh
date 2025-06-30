#!/bin/sh

for o in dme sce cel hpy eco
do
    l=$o
    for i in 3
    do 
	r=`./stat_sampling "$o"_undirected $i 1`
	l="$l\t$r"
	#echo "$2\t$3\t$i\t$r"
    done
    echo $l
done


