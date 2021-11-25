#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <random>

using namespace std::chrono;

using namespace std;

int **matrix_1;
int **matrix_2;
int **matrix_3;
int TAMANIO;
int numHilos;


void mult(){

	omp_set_num_threads(numHilos);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int numeroDeHilos = omp_get_num_threads();
		int tamanio = (int) TAMANIO / numeroDeHilos;
		int inicio = id * tamanio;
		int fin = inicio + tamanio;
		//cout<<" numero de hilo: "<< id << endl;


		for (int i=0; i<TAMANIO; i++){ 
			for (int j=inicio; j<fin; j++){
				matrix_3[i][j] = 0; 
				for (int k=0; k<TAMANIO; k++){
					matrix_3[i][j] = matrix_3[i][j] + matrix_1[i][k] * matrix_2[k][j];
				}
			}
		}
	}

}


int main(int argc, char const *argv[])
{
    int i, j;

    TAMANIO = atoi(argv[1]);

    numHilos = atoi(argv[2]);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);



    matrix_1 = (int **) malloc (sizeof (int *) * TAMANIO);
    matrix_2 = (int **) malloc (sizeof (int *) * TAMANIO);
    matrix_3 = (int **) malloc (sizeof (int *) * TAMANIO);

    for (i = 0; i < TAMANIO; i++)
        matrix_1[i] = (int *) malloc (sizeof (int) * TAMANIO);
    for (i = 0; i < TAMANIO; i++)
        matrix_2[i] = (int *) malloc (sizeof (int) * TAMANIO);
    for (i = 0; i < TAMANIO; i++)
        matrix_3[i] = (int *) malloc (sizeof (int) * TAMANIO);

  
    
    for (i = 0; i < TAMANIO; i++) {
        for (j = 0; j < TAMANIO; j++) {
            matrix_1[i][j] = dist(mt);
        }
    }

    for (i = 0; i < TAMANIO; i++) {
        for (j = 0; j < TAMANIO; j++) {
            matrix_2[i][j] = dist(mt);
        }
    }


    auto start = high_resolution_clock::now();

    mult();

    auto stop = high_resolution_clock::now();

    std::chrono::duration<double> duration = stop - start;

    cout <<duration.count();


/*     printf ("\n\nFinal a :");
    for (i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_1[i][j]);
    }

    printf ("\n\nFinal b :");
    for (i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_2[i][j]);
    }

    printf ("\n\nFinal Matrix :");
    for (i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_3[i][j]);
    }
*/
    for(i = 0; i < TAMANIO; i++)
        {
            free(matrix_1[i]);
            free(matrix_2[i]);
            free(matrix_3[i]);

        }

    free(matrix_1);
    free(matrix_2);
    free(matrix_3); 

    return 0;
}
