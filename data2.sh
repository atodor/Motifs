#!/bin/sh

for i in dme sce cel hpy eco
do
echo $i
./data ../Data/MINT/$i.txt "$i"_directed 1
./data ../Data/MINT/$i.txt "$i"_undirected 0
done

