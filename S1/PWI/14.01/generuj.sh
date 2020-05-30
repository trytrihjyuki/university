#!/bin/bash


DIFFERENCE=$1
OUTPUT_FILE='dane2.dat'

g++ -o sort sort.cpp 
echo "Wielkość BubbleSort STLSort" > $OUTPUT_FILE
for i in {1..100};
do
    echo "Generuje dane dla wielkości: "$(($1*$i*1/10))
    ./sort $(($1*$i*1/10)) >> $OUTPUT_FILE
done

rm sort

gnuplot -p skrypt_2
