#!/bin/sh

for i in dme sce cel hpy eco
do
for j in `seq 100` 
do
./data ../Data/MINT/Artificial/$i$j.txt "$i$j"_undirected 0
done
done

