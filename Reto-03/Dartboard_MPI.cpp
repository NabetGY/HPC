#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <random>
#include <unistd.h>
#include <mpi.h>

using namespace std::chrono;

using namespace std;
double Inicio, Fin;

int main(int argc, char *argv[]){

    int miID, numProcs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &miID);

    MPI_Status status;
    long k, n, hits = 0;
    n = atoi(argv[1]);
    if (miID != 0){

        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_real_distribution<double> dist(0, 1);

        long hitsAux;
        
        for (k = hitsAux = 0; k < n/(numProcs-1); ++k)
        {
            double x = dist(mt);
            double y = dist(mt);
            if (x * x + y * y < 1.0) // Está dentro del circulo?
                ++hitsAux;
        }

        MPI_Send(&hitsAux,1,MPI_LONG,0,3,MPI_COMM_WORLD);
    }
    
    if (miID == 0){

        Inicio =  MPI_Wtime ();
    
        for(int i = 1; i < numProcs; i++ )
            {
                long resultado = 0;
                MPI_Recv(&resultado,1,MPI_LONG,i, 3,MPI_COMM_WORLD, &status);

                hits += resultado;
            }
        Fin =  MPI_Wtime (); 

        double resultado = Fin - Inicio;
        printf ("%f", resultado);

        double pi_approx = 4.0 * hits / n;

/*         cout << "\npi : " << pi_approx << endl;
 */
    }

    MPI_Finalize();
    return 0;
}
