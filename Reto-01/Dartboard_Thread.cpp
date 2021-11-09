#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <chrono>
#include <random>
using namespace std::chrono;

using namespace std;





// n -> es el numero de lanzamientos
// hits -> numero de golpes

long n, hitsFinal;
const double factor = 1.0/RAND_MAX;

int numHilos;

void *area(void* arg){
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
    pthread_exit(0);
}

int main(int argc, char const *argv[]){
    
    int i;
    
    numHilos = atoi(argv[2]);
    
    pthread_t misHilos[numHilos];
    
    while (1)
    {
        n = atoi(argv[1]);
        if (n <=0 )
            break;
        //srand((int)clock()); //Inicializa el generador de random

        
        //clock_t start = clock();
        auto start = high_resolution_clock::now();
        for (i = 0; i < numHilos; i++)
            {
                pthread_create(&misHilos[i], NULL, area, NULL);
            }
        
        
        for (i = 0; i < numHilos; i++)
            {
                pthread_join(misHilos[i], NULL);
            }
        auto stop = high_resolution_clock::now();

        cout << "Factor: " <<factor<<endl;

        std::chrono::duration<double> duration = stop - start;
        cout << "Tiempo new function: " <<duration.count() << endl;

        // clock_t end = clock();
        // double elapsed = (double)(end - start)/CLOCKS_PER_SEC;
        // printf("Tiempo: %.3f\n", elapsed);
        // cout << "inicio: " << start/1000000 <<endl;
        // cout << "End: " << end/1000000 <<endl;
        

        cout << "Soy hits FINAL: " << hitsFinal <<endl;
        double pi_approx = 4.0 * hitsFinal/n;
        cout << "Aproximación: "
        << pi_approx
        << " (error = "
        << fabs(M_PI - pi_approx)*100/M_PI
        << "%)\n)";

        break;
        
    }
    return 0;
    
}