#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

//hola compañeros

double Inicio, Fin;

int main(int argc, char *argv[])
{
    int miID, numProcs;

    MPI_Init(&argc, &argv);




    time_t t;
    double **matrix_1, **matrix_2, **matrix_3;
    int N; 
    int i, j, k, m;

    N = atoi(argv[1]);

    matrix_1 = (double **) malloc (sizeof (double *) * N);
    matrix_2 = (double **) malloc (sizeof (double *) * N);
    matrix_3 = (double **) malloc (sizeof (double *) * N);

    for (i = 0; i < N; i++)
        matrix_1[i] = (double *) malloc (sizeof (double) * N);
    for (i = 0; i < N; i++)
        matrix_2[i] = (double *) malloc (sizeof (double) * N);
    for (i = 0; i < N; i++)
        matrix_3[i] = (double *) malloc (sizeof (double) * N);

  
    
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrix_1[i][j] = rand ();
            }
        }

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrix_2[i][j] = rand ();
            }
        }

    
    
  

        Inicio =  MPI_Wtime ();

    

        for (int  c = 0; c < N; c++)
        {        
            for(int b=0; b<N; b++)
            {
                matrix_3[c][b] = 0;
                for (int a = 0; a < N; a++)
                    {
                        matrix_3[c][b] = matrix_3[c][b] + (matrix_1[c][a] * matrix_2[b][a]);
                    }                   
            }
        }
        Fin =  MPI_Wtime (); 

    MPI_Finalize();


  

        //Printing the contents of third matrix. 

    

        /* code */

        for(i = 0; i < N; i++){
            free(matrix_1[i]);
            free(matrix_2[i]);
            free(matrix_3[i]);

        }

        free(matrix_1);
        free(matrix_2);
        free(matrix_3);

        double resultado = Fin - Inicio;
        printf ("%f", resultado);


    

        //printf ("\n");
        //printf ("tiempo : %4f segundos \t", Fin-Inicio);
    return (0);
    
}
