#!/bin/bash

lista=( 100 200 400 800 1200 1600 2000);


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(./mxm2.out $i 4),"
        done
    echo $variable>>result.csv        
    done
