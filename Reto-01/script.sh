#!/bin/bash

lista=( 100000 1000000 100000000 200000000 300000000 400000000 500000000);


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(./mxm2.out $i, 4),"
        done
    echo $variable>>result.csv        
    done
