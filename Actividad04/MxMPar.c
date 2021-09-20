#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int **matrix_1;
int **matrix_2;
int **matrix_3;
int TAMANIO;
int SEGMENTO;


void multi(int shift) {

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

void imprimirMatrix();

int main(int argc, char const *argv[])
{
    int i, j, numHijos, status;

    pid_t pidC;





    TAMANIO = atoi(argv[1]);

    numHijos = atoi(argv[2]);

    SEGMENTO = TAMANIO/numHijos;



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
            matrix_1[i][j] = rand () % 10;
        }
    }

    for (i = 0; i < TAMANIO; i++) {
        for (j = 0; j < TAMANIO; j++) {
            matrix_2[i][j] = rand () % 10;
        }
    }


    clock_t start = clock();

    for (i = 0; i < numHijos; i++)
    {
        int salto = i*SEGMENTO;

        pidC = fork();
        if (pidC > 0)
        {
            continue;
        }else if (pidC == 0)
        {
            multi(salto);
            sleep(5);
          //  exit(1);
        } else
        {
            printf("Error detectado...");
        }
    
    }
    
    for (i = 0; i < numHijos; i++)
    {
        pidC = wait(&status);
    }

    clock_t end = clock();

    double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

    if (pidC > 0)
    {
        printf("%.3f pid papi: %d \n", elapsed, getpid());
        
    }
    imprimirMatrix();
    
/*         printf ("\n\nFinal Matrix :pid : %d \n", getpid());
    for (int i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (int j = 0; j < TAMANIO; j++)
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












void imprimirMatrix()
{
    printf ("\n\nFinal a | pid : %d \n", getpid());
    for (int i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_1[i][j]);
    }

    printf ("\n\nFinal b | pid : %d \n", getpid());
    for (int i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_2[i][j]);
    }

    printf ("\n\nFinal Matrix | pid : %d \n", getpid());
    for (int i = 0; i < TAMANIO; i++) {
        printf ("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf ("%i \t", matrix_3[i][j]);
    }
}