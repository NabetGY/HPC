#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <wait.h>
#include <stdlib.h>


int TAMANIO;
int SEGMENTO;

unsigned int sizeof_dm(int rows, int cols, size_t sizeElement){
    size_t size = rows * (sizeof(void *) + (cols * sizeElement));
    return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement){
    int i;  
    size_t sizeRow = cols * sizeElement;
    m[0] = m+rows;
    for(i=1; i<rows; i++){      
        m[i] = (m[i-1]+sizeRow);
    }
}

void print_matriz(int **matrix, int Rows, int Cols){
    printf("\n");
        for(int i=0; i<Rows; i++){
            for(int j=0; j<Cols; j++)
                printf("%.2f\t",matrix[i][j]);
            printf("\n");
        }
}

int main(int argc, char **argv){

    int **matrix;
    int **matrixA;
    int **matrixB;
    int Cols = 10, Rows = 5, shmId;
    int i, j, numHijos, status;

    pid_t pidC;
    TAMANIO = 8;

    numHijos = 4 ; //atoi(argv[2]);


    size_t sizeMatrix = sizeof_dm(TAMANIO,TAMANIO,sizeof(int));
    shmId = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT|0600);    
    int shmId2 = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT|0600);    
    int shmId3 = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT|0600);    

    matrix = shmat(shmId, NULL, 0); 
    create_index((void*)matrix, TAMANIO, TAMANIO, sizeof(int));
    matrixA = shmat(shmId2, NULL, 0); 
    create_index((void*)matrixA, TAMANIO, TAMANIO, sizeof(int));
    matrixB = shmat(shmId3, NULL, 0); 
    create_index((void*)matrixB, TAMANIO, TAMANIO, sizeof(int));

            int pos=0;
        for(int i=0; i<TAMANIO; i++){
            for(int j=0; j<TAMANIO; j++)
            {
                matrixB[i][j] =  rand() % 10;
                matrixA[i][j] =  rand() % 10;
            }  
        }

    SEGMENTO = TAMANIO/numHijos;
    int shift = 0;
    for (int i = 0; i < numHijos; i++)
    {    
        shift = i*SEGMENTO;
        pidC = fork();
        if(pidC==0){
            int a, b, c;

            for (c = shift; c < SEGMENTO+shift; c++)
                {        
                    for(b = 0; b < TAMANIO; b++)
                    {
                        matrix[c][b] = 0;
                        for (a = 0; a < TAMANIO; a++)
                            {
                                matrix[c][b] = matrix[c][b] + (matrixA[c][a] * matrixB[a][b]);
                            }                   
                    }
                }

    printf("Matrix final: \n\t");
    printf("--*******************------------");
    
    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf("%i \t", matrix[i][j]);
    }
    printf("----------------------------------");
            shmdt(matrix);
            exit(1);
        }
        sleep(3);
        }

    wait(&status);
    shmctl(shmId, IPC_RMID, 0);

    printf("Matrix A: \n\t");
    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf("%i \t", matrixA[i][j]);
    }

    printf("Matrix B: \n\t");
    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf("%i \t", matrixB[i][j]);
    }

    printf("Matrix final: \n\t");
    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\n\t");
        for (int j = 0; j < TAMANIO; j++)
            printf("%i \t", matrix[i][j]);
    }
    return 0;
}