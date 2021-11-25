#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <chrono>
#include <omp.h>
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

void coprimo(){

    omp_set_num_threads(numHilos);

	#pragma omp parallel
	{
        long hits, nTries;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, RAND_MAX);

        for (nTries = hits=0; nTries <n/numHilos; ++nTries){
                int A = dist(mt) + 1;
                int C = dist(mt) + 1;
                if (euclid(A, C) == 1) // A and C are relative prin
                    ++hits;
            }
            hitsFinal+= hits;

            cout << "hits: " << hits << endl;
    
    }
    
}

int main (int argc, char const *argv[]){

    int i;
    
    numHilos = atoi(argv[2]);

    n = atoi(argv[1]);

    if (n <= 0) return 0;
    
    auto start = high_resolution_clock::now();

    coprimo();
    
    auto stop = high_resolution_clock::now();

    std::chrono::duration<double> duration = stop - start;

    cout <<duration.count();

    double f = hitsFinal * 1.0/n;
    double pi = sqrt(6.0/ f); 

            cout << "\nhitsFinal: " << hitsFinal << endl;
            cout << "\npi: " << pi << endl;



    return 0;
}

