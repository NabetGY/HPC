#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 

int **matrix_1;
int **matrix_2;
int **matrix_3;
int TAMANIO;
int SEGMENTO;


void *multi(int shift) {

    int a, b, c;

    for (c = shift; c < SEGMENTO+shift; c++)
        {        
            for(b = 0; b < TAMANIO; b++)
            {
                matrix_3[c][b] = 0;
                for (a = 0; a < TAMANIO; a++)
                    {
                        matrix_3[c][b] = matrix_3[c][b] + (matrix_1[c][a] * matrix_2[a][b]);
                    }                   
            }
        }

}


int main(int argc, char const *argv[])
{
    int i, j, numHilos;


    TAMANIO = atoi(argv[1]);

    numHilos = atoi(argv[2]);

    SEGMENTO = TAMANIO/numHilos;

    pthread_t misHilos[numHilos];


    /* printf("segmento main: %i", SEGMENTO);
    printf ("\n\t"); */

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
            matrix_1[i][j] = rand () % 10000;
        }
    }

    for (i = 0; i < TAMANIO; i++) {
        for (j = 0; j < TAMANIO; j++) {
            matrix_2[i][j] = rand () % 10000;
        }
    }


    clock_t start = clock();

    for (int i = 0; i < numHilos; i++)
    {
        pthread_create(&misHilos[i], NULL, (void *) multi, i*SEGMENTO);
    }
    
    for (int i = 0; i < numHilos; i++)
    {
        pthread_join(misHilos[i], NULL);
    }

    clock_t end = clock();

    double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

    printf("%.3f", elapsed);
    
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
    } */

    for(i = 0; i < TAMANIO; i++)
        {
            free(matrix_1[i]);
            free(matrix_2[i]);
            free(matrix_3[i]);

        }

        printf ("\n\t");

    free(matrix_1);
    free(matrix_2);
    free(matrix_3);

    return 0;
}
