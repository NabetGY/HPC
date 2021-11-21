#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <wait.h>
#include <stdlib.h>
#include <time.h>

int TAMANIO;
int SEGMENTO;

float time_diff2(struct timespec *start, struct timespec *end){
    return (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
}


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


int main(int argc, char **argv){

    int **matrix;
    int **matrixA;
    int **matrixB;
    int numHijos, status, shmId;
    struct timespec start2;
    struct timespec end2;

    pid_t pidC;

    TAMANIO = atoi(argv[1]);

    numHijos = atoi(argv[2]);


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


    for(int i=0; i<TAMANIO; i++){
        for(int j=0; j<TAMANIO; j++)
            {
                matrixB[i][j] =  rand() % 10;
                matrixA[i][j] =  rand() % 10;
            }  
        }

    SEGMENTO = TAMANIO/numHijos;
    int shift = 0;

    clock_gettime(CLOCK_REALTIME, &start2);
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
            shmdt(matrix);
            exit(EXIT_SUCCESS);
        }
    }

    wait(NULL);
    clock_gettime(CLOCK_REALTIME, &end2);
    printf("%.3f", time_diff2(&start2, &end2));

    shmctl(shmId, IPC_RMID, 0);
    return 0;
}