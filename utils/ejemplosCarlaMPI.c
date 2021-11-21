###############0#################

#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){
   int my_id, nproc, tag = 99, source;
  
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   MPI_Comm_size(MPI_COMM_WORLD, &nproc);

   printf("I am processor %d from a total of %d\n",my_id,nproc);

   MPI_Finalize();
}


##############1######################

#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[])
{ char machine_name[MPI_MAX_PROCESSOR_NAME];
  int MyId, N, value, namelength;

  MPI_Init (&argc, &argv);
  
  MPI_Comm_rank (MPI_COMM_WORLD, &MyId); 
  MPI_Comm_size (MPI_COMM_WORLD, &N);
  srand(MyId);
  MPI_Get_processor_name(machine_name,&namelength); 
  value= (rand() % 100);
  printf("Hi, I am process %d from %d. I calculate %d. Running on %s\n",MyId,N,value,machine_name); 
  
  
  MPI_Finalize();
  
return 0;
}

####################2####################

#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){
   int my_id, nproc, tag = 99, source;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   MPI_Comm_size(MPI_COMM_WORLD, &nproc);

   MPI_Send(&my_id, 1, MPI_INT, (my_id+1)%nproc, tag, 
                   MPI_COMM_WORLD);
   //int DoSomeWork();
   MPI_Recv(&source,1,MPI_INT,MPI_ANY_SOURCE,tag,
                  MPI_COMM_WORLD, &status);

   printf("I am process %d and received a message from %d\n",my_id,source);

   MPI_Finalize();
}

####################3############################

#include <stdio.h>
#include <mpi.h>
#define LIM 10
int main (int argc, char *argv[]) {
  double inicio,final;
  int i,error, MyId, N;
  int buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status;
  MPI_Init (&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &N);
  if (N != 2) {
    printf(stderr,"This program only runs on TWO processors. set -np 2");
    MPI_Finalize();
    exit(1);
  }

  if (MyId == 0)
  { 
    inicio=MPI_Wtime();
    printf("time 1, process 0: %lf\n",inicio);
    MPI_Send(buff, LIM, MPI_INT, 1, 111, MPI_COMM_WORLD);
    final=MPI_Wtime();
    printf("time 2, process 0: %lf\n",final);
    printf("process %d, sent:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    inicio=MPI_Wtime();
    printf("time 3, process 0: %lf\n",inicio);
    MPI_Recv(buff, LIM, MPI_INT, 1, 222, MPI_COMM_WORLD, &status);
    final=MPI_Wtime();
    printf("time 4,process 0: %lf\n",final);
    printf("process %d, received all messages:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

  } else
    {  
    inicio=MPI_Wtime();
    printf("time 1,process 1: %lf\n",inicio);
    MPI_Recv(buff, LIM, MPI_INT, 0, 111, MPI_COMM_WORLD, &status);
    final=MPI_Wtime();
    printf("time 2, process 1: %lf\n",final);
    printf("process %d, received :\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    for (i=0;i<LIM;i++) 
      buff[i]++; 
    inicio=MPI_Wtime();
    printf("time 3, process 1:%lf\n",inicio);
    MPI_Send(buff, LIM, MPI_INT, 0, 222, MPI_COMM_WORLD);
    final=MPI_Wtime();
    printf("time 4, process 1:%lf\n",final);
    printf("process %d, send:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    final=MPI_Wtime();
    printf(" \n");
    printf("time 5, process 1: %lf\n",final);
 }

  MPI_Finalize();
  exit(0);
}


###############4##############################

// Ejemplo de Comunicacion Asincrona
//
#include <stdio.h>
#include <mpi.h>
#define LIM 10
main (int argc, char *argv[]) {
  double init,final;
  int i,error, MyId, p;
  int finish,
  buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status[LIM];
  MPI_Request reque[LIM];
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  if (p != 2) {
    fprintf("This program only runs on TWO processors. set -np 2");
    MPI_Finalize();
    exit(1);
  }
  if (MyId == 0)
  { 
    init=MPI_Wtime();
    printf("Before: %lf\n",init);
    for (i=0;i<LIM;i++) 
    {
         MPI_Isend(&(buff[i]), 1, MPI_INT, 1, 111,MPI_COMM_WORLD,&(reque[i]));
         final=MPI_Wtime();
         printf("%d,After %d, %lf\n",MyId,i,final);
    } 
    printf("Process %d, sent:\n", MyId);
    for (i=0;i<LIM;i++) 
         printf("{%d,%d}",MyId,buff[i]);
    MPI_Waitall(LIM,reque,status);
    final=MPI_Wtime();
    final=MPI_Wtime();
    printf("Process %d, end \n", MyId,final);
  } else
    {  
    init=MPI_Wtime();
    printf("%lf\n",init);
    for (i=0;i<LIM;i++) 
    {
        buff[i]=5555;  
        MPI_Irecv(&(buff[i]),1,MPI_INT, 0, 111, MPI_COMM_WORLD,&(reque[i]));
        printf("Process %d, buff[%d]= %d \n",MyId,i,buff[i]);
   }
//  
// MPI_Test(&(reque[4]),&finish,&(status[4]));
    MPI_Wait(&(reque[3]),&(status[4]));
 
           printf("Process %d, received messages \n", MyId); 

    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
 }
  MPI_Finalize();
  exit(0);
}


###################5####################

#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define lim 20

int buf[lim]=
{27,65,3,8,45,10,50,95,10,11,9,48,69,25,19,29,61,42,93,20};
int buf2[5];
int buf3[4];
int max;
int main(int argc, char *argv[])
{
int n, myid, numprocs, i;
int namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&myid);
MPI_Get_processor_name(processor_name,&namelen);
printf("Process %d \n",myid);
n=lim/numprocs;
MPI_Scatter(buf,n, MPI_INT,buf2,n,MPI_INT, 0, MPI_COMM_WORLD);
for (i=0; i<n ; i++)
printf("Process %d Buf2[%d]= %d \n", myid, i, buf2[i]);
MPI_Reduce(buf2,buf3,n, MPI_INT, MPI_MAX, 0,MPI_COMM_WORLD);
if (myid == 0)
{ max = buf3[0];
for (i=1; i<n ; i++)
if (max < buf3[i]) max = buf3[i]; 
for (i=0; i<n ; i++)
printf("Buf3[%d]= %d \n", i, buf3[i]);
printf("Max value is : %d ", max);
}
MPI_Finalize();
return 0;
}

