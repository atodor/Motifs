#!/bin/sh

for i in 1 2 3
do 
r=`./stat $1_undirected $i`
echo "$2\t$3\t$i\t$r"
done

for i in 4 5 6 7 8 9 10 11 12 13 14
do 
r=`./stat $1_directed $i`
echo "$2\t$3\t$i\t$r"

done

