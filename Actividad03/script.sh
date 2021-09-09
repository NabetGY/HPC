#!/bin/bash

lista=( 90 120 150 210 240 270 300 600 900 1200 1500 1800 2100 2700 );


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(./mxm.out $i),"
        done
    echo $variable>>result.csv        
    done
