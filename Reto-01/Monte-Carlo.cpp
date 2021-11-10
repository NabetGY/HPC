#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <random>
using namespace std::chrono;

using namespace std;

std::random_device rd;
std::mt19937 mt(rd());

int euclid(int u, int v){
    int r;
    while ((r = u % v) != 0){
        u = v;
        v= r;
    }
    return v;
}

int main (int argc, char const *argv[]){
    while (1){
        int n, nTries, nHits;
        
        n = atoi(argv[1]);

        if (n <= 0) break;
        
        std::uniform_real_distribution<double> dist(0, RAND_MAX);

        auto start = high_resolution_clock::now();

        for (nTries = nHits=0; nTries <n; ++nTries){
            int A = dist(mt) + 1;
            int C = dist(mt) + 1;
            if (euclid(A, C) == 1) // A and C are relative prin
                ++nHits;
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        
        cout <<duration.count();

        double f = nHits * 1.0/nTries;
        double pi = sqrt(6.0/ f); 
        break;
    }
    return 0;
}

