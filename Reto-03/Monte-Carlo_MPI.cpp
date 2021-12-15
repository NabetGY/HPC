#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <random>
#include <unistd.h>
#include <mpi.h>


using namespace std;

double Inicio, Fin;


int euclid(int u, int v){
    int r;
    while ((r = u % v) != 0){
        u = v;
        v= r;
    }
    return v;
}

int main (int argc, char *argv[]){

    int miID, numProcs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &miID);

    MPI_Status status;
        
    long n;
        
    n = atoi(argv[1]);

        if (miID != 0){
            long hits, nTries;
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, RAND_MAX);

            for (nTries = hits=0; nTries <n/(numProcs-1); ++nTries){
                    int A = dist(mt) + 1;
                    int C = dist(mt) + 1;
                    if (euclid(A, C) == 1) // A and C are relative prin
                        ++hits;
                }
            long hitsFinal = hits;
            
            MPI_Send(&hitsFinal,1,MPI_LONG,0,3,MPI_COMM_WORLD);
        }
    
     if (miID == 0){

         long nHits = 0;

         Inicio =  MPI_Wtime ();

        for (int i = 1; i < numProcs; i++){
            long aux = 0;
            MPI_Recv(&aux,1,MPI_LONG,i, 3,MPI_COMM_WORLD, &status);
            nHits += aux;
        }

        Fin =  MPI_Wtime (); 

        double resultado = Fin - Inicio;
        printf ("%f", resultado);

        double f = nHits * 1.0/n;
        double pi = sqrt(6.0/ f);
    }

    MPI_Finalize();
    return 0;
}

