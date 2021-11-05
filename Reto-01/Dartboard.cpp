#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

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
        srand((int)clock()); //Inicializa el generador de random

        clock_t start = clock();

        for (k=hits=0; k < n; ++k)
        {
            double x = rand() * factor;
            double y = rand() * factor;
            if (x*x + y*y < 1.0) // Está dentro del circulo?
                ++hits;
        }

        clock_t end = clock();
        double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

        printf("Tiempo: %.3f \n", elapsed);

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