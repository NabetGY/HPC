#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int **matrix_1;
int **matrix_2;
int **matrix_3;
int TAMANIO;

float time_diff2(struct timespec *start, struct timespec *end){
    return (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
}

void *multi() {

    int a, b, c;

    for (c = 0; c < TAMANIO; c++)
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
    int i, j;
    struct timespec start2;
    struct timespec end2;

    TAMANIO = atoi(argv[1]);

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


    clock_gettime(CLOCK_REALTIME, &start2);

    multi();

    clock_gettime(CLOCK_REALTIME, &end2);
    printf("%.3f", time_diff2(&start2, &end2));
    
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

    free(matrix_1);
    free(matrix_2);
    free(matrix_3);

    return 0;
}
