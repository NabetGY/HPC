#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <chrono>
#include <random>
using namespace std::chrono;

using namespace std;


int numHilos;
long n;
long hitsFinal;


int euclid(int u, int v){
    int r;
    while ((r = u % v) != 0){
        u = v;
        v= r;
    }
    return v;
}

void *coprimo(void* arg){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, RAND_MAX);
    long hits, nTries;
    for (nTries = hits=0; nTries <n/numHilos; ++nTries){
            int A = dist(mt) + 1;
            int C = dist(mt) + 1;
            if (euclid(A, C) == 1) // A and C are relative prin
                ++hits;
        }
        hitsFinal+= hits;
    pthread_exit(0);
}

int main (int argc, char const *argv[]){

    int i;
    
    numHilos = atoi(argv[2]);
    
    pthread_t misHilos[numHilos];

    while (1){
        
        n = atoi(argv[1]);

        if (n <= 0) break;
        
        std::uniform_real_distribution<double> dist(0, RAND_MAX);

        auto start = high_resolution_clock::now();

        for (i = 0; i < numHilos; i++){
            pthread_create(&misHilos[i], NULL, coprimo, NULL);
        }
        
        for (i = 0; i < numHilos; i++){
            pthread_join(misHilos[i], NULL);
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        cout <<duration.count();

        double f = hitsFinal * 1.0/n;
        double pi = sqrt(6.0/ f); 
        cout << "\npi: " << pi << endl;


        break;
    }
    return 0;
}

