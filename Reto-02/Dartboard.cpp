#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <random>
#include <omp.h>

using namespace std::chrono;

using namespace std;

// n -> es el numero de lanzamientos
// hits -> numero de golpes

long n, hitsFinal;
const double factor = 1.0/RAND_MAX;

int numHilos;

void area(){

    omp_set_num_threads(numHilos);
	#pragma omp parallel  
    { 
        long k, hits;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, 1);
        for (k=hits=0; k < n/numHilos; ++k)
            {   
                double x = dist(mt);
                double y = dist(mt);
                if (x*x + y*y < 1.0) // Está dentro del circulo?
                    ++hits;
                    
            }
            hitsFinal+= hits;
    }
}

int main(int argc, char const *argv[]){
    
    int i;
    
    numHilos = atoi(argv[2]);
        
    n = atoi(argv[1]);
    if (n <=0 )
        return 0;

    auto start = high_resolution_clock::now();

    area();

    auto stop = high_resolution_clock::now();

    std::chrono::duration<double> duration = stop - start;

    cout <<duration.count();

    double pi_approx = 4.0 * hitsFinal/n;

    return 0;
}