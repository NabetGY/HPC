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

int main(void){
    long k,n,hits;
    const double factor= 1.0/RAND_MAX;
    
    while (1)
    {
        cout << "Ingrese el N° de lanzamientos (o 0 para salir): ";
        cin >> n;
        if (n <=0 )
            break;
        
        std::uniform_real_distribution<double> dist(0, 1);
        auto start = high_resolution_clock::now();

        for (k=hits=0; k < n; ++k)
        {   
            double x = dist(mt) ;
            double y = dist(mt) ;
            //cout << "Soy X: "<<x<<endl;
            if (x*x + y*y < 1.0) // Está dentro del circulo?
                ++hits;
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        
        cout << "Tiempo new function: " <<duration.count() << endl;
        double rando = rand();
        cout << "rand: " <<rando<<endl;
        


        double pi_approx = 4.0 * hits/n;
        cout << "Aproximación: "
        << pi_approx
        << " (error = "
        << fabs(M_PI - pi_approx)*100/M_PI
        << "%)\n)";

        break;
        
    }
    return 0;
    
}