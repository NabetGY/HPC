#!/bin/bash

lista=( 100 200 400 800 1200 1600 2000 );


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(./mxm.out $i),"
        done
    echo $variable>>result.csv        
    done
