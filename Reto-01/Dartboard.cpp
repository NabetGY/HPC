#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <random>
using namespace std::chrono;

using namespace std;

std::random_device rd;
std::mt19937 mt(rd());

// n -> es el numero de lanzamientos
// hits -> numero de golpes

int main(int argc, char const *argv[]){
    long k,n,hits;
    const double factor= 1.0/RAND_MAX;
    
    while (1)
    {
        n = atoi(argv[1]);
        if (n <=0 )
            break;
        
        std::uniform_real_distribution<double> dist(0, 1);
        auto start = high_resolution_clock::now();

        for (k=hits=0; k < n; ++k)
        {   
            double x = dist(mt) ;
            double y = dist(mt) ;
            if (x*x + y*y < 1.0) // Está dentro del circulo?
                ++hits;
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        cout <<duration.count();
        
        double pi_approx = 4.0 * hits/n;

        break;
        
    }
    return 0;
    
}