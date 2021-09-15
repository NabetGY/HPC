#!/bin/bash

<<<<<<< HEAD
lista=( 100 200 400 800 1200 1600 2000 );
=======
lista=( 100 200 400 800 1200 1600 2000);
>>>>>>> 5f2e037980d4c83d7a3c102b236c11219e10af16


for i in ${lista[@]};
    do
    variable="$i,"
    for (( j=0; j<10; j++ ));
        do
        variable+="$(./mxm2.out $i 4),"
        done
    echo $variable>>result.csv        
    done
