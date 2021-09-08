#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char const *argv[])
{
    int **matrix_1, **matrix_2, **matrix_3;
    int N; 
    int i, j;


    N = atoi(argv[1]);

    matrix_1 = (int **) malloc (sizeof (int *) * N);
    matrix_2 = (int **) malloc (sizeof (int *) * N);
    matrix_3 = (int **) malloc (sizeof (int *) * N);

    for (i = 0; i < N; i++)
        matrix_1[i] = (int *) malloc (sizeof (int) * N);
    for (i = 0; i < N; i++)
        matrix_2[i] = (int *) malloc (sizeof (int) * N);
    for (i = 0; i < N; i++)
        matrix_3[i] = (int *) malloc (sizeof (int) * N);

  
    
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


    clock_t start = clock();

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

    clock_t end = clock();
    double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

    printf("Tiempo obtenido: %.3f seconds.\n", elapsed);
    printf("Tiempo begin: %u seconds.\n", start);
    printf("Tiempo end: %u seconds.\n", end);
    printf("Tiempo end: %u seconds.\n", CLOCKS_PER_SEC);



    for(i = 0; i < N; i++)
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
