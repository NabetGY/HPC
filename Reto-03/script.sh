#!/bin/bash

lista=( 100000 1000000 10000000 20000000 30000000 400000000 500000000);


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(mpiexec --hosts head,wn2,wn3 Dartboard.out $i),"
        done
    echo $variable>>result.csv        
    done
