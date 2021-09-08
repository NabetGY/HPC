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
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &miID);

    MPI_Status status;

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

    if(miID == 0)
    {
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

    }
    
    if(miID == 0)
    {
        //printf("\n entre al master ");

        Inicio =  MPI_Wtime ();
        int tamanio = N / (numProcs-1);
        
        MPI_Send(&tamanio,1,MPI_INT,1,7,MPI_COMM_WORLD);

        MPI_Send(&tamanio,1,MPI_INT,2,7,MPI_COMM_WORLD);

        MPI_Send(&tamanio,1,MPI_INT,3,7,MPI_COMM_WORLD);

        int comienzo = 0;

        int final = tamanio;

        for(j = 1; j < numProcs ; j++)
        {
            MPI_Send(&comienzo,1,MPI_INT,j,8,MPI_COMM_WORLD);

            MPI_Send(&final,1,MPI_INT,j,9,MPI_COMM_WORLD);

            for(int i = comienzo; i < final; i++ )
            {
                MPI_Send(matrix_1[i],N,MPI_DOUBLE,j,1,MPI_COMM_WORLD);
            }
        
            comienzo = final;

            final = final + tamanio;
        }


        for(j = 1; j < numProcs ; j++)
        {
            for(int i = 0; i < N; i++ )
            {
                MPI_Send(matrix_2[i],N,MPI_DOUBLE,j,2,MPI_COMM_WORLD);
            }
        }


        comienzo = 0;

        final = tamanio;

        for(int j = 1; j < numProcs ; j++)
        {
            for(int i = comienzo; i < final; i++ )
            {
                MPI_Recv(matrix_3[i],N,MPI_DOUBLE,j,3,MPI_COMM_WORLD,&status);
            }
        
            comienzo = final;

            final = final + tamanio;
        }

        Fin =  MPI_Wtime (); 
    }
   
    if(miID!=0)
    {
        int tamanio=0;

        int comienzo, final;

        //printf("\n recibiendo matrix 1 ");

        MPI_Recv(&tamanio,1,MPI_INT,0,7,MPI_COMM_WORLD, &status);

        MPI_Recv(&comienzo,1,MPI_DOUBLE,0,8,MPI_COMM_WORLD, &status);

        MPI_Recv(&final,1,MPI_DOUBLE,0,9,MPI_COMM_WORLD, &status);

        for(int i = 0; i < tamanio; i++)
        {
            MPI_Recv(matrix_1[i],N,MPI_DOUBLE,0,1,MPI_COMM_WORLD, &status);
        }




        for(int i = 0; i < N; i++)
        {
           MPI_Recv(matrix_2[i],N,MPI_DOUBLE,0,2,MPI_COMM_WORLD, &status);
        }



        //printf("\n soy el procesador: %d y recibi los datos, valor de N: %d\n",miID,N);


        for (int  c = 0; c < tamanio; c++)
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


        for(int i = 0; i < tamanio; i++)
        {
            MPI_Send(matrix_3[i],N,MPI_DOUBLE,0,3,MPI_COMM_WORLD);
        }



        for(i = 0; i < N; i++)
        {
            free(matrix_1[i]);
            free(matrix_2[i]);
            free(matrix_3[i]);
        }

        free(matrix_1);
        free(matrix_2);
        free(matrix_3);


    }
    


            
        

    MPI_Finalize();


    if (miID ==0)
    {

        /* Printing the contents of third matrix. 
        printf ("\n\nMatrix 1:");
        for (i = 0; i < N; i++) {
            printf ("\n\t");
            for (j = 0; j < N; j++)
                printf ("%2.1f \t", matrix_1[i][j]);
        }

        printf ("\n\nMatrix 2:");
        for (i = 0; i < N; i++) {
            printf ("\n\t");
            for (j = 0; j < N; j++)
                printf ("%2.1f \t", matrix_2[i][j]);
        }
    

        printf ("\n\nFinal Matrix :");
        for (i = 0; i < N; i++) {
            printf ("\n\t");
            for (j = 0; j < N; j++)
                printf ("%2.1f \t", matrix_3[i][j]);
        }*/
    

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


    }

        //printf ("\n");
        //printf ("tiempo : %4f segundos \t", Fin-Inicio);
    return (0);
    
}
