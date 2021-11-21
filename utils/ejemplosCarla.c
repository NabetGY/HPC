int main(char **argv,int argc)
{  
#pragma omp parallel
     printf("Hello world\n");
exit (0);
}
################1#############

int main(char **argv,int argc)
{ int privateX=0;  
#pragma omp parallel
{ int sharedX=0;
  privateX++;
  sharedX++;
  printf("privateX %d sharedX %d\n",
         privateX,sharedX);
}
exit (0);
}

###################2############

#include <stdlib.h>
#include <stdio.h>

int main(char **argv,int argc)
{ int i=0; 
#pragma omp parallel for
     for (i=0;i<1000;i++)
         printf("%d \n",i);
exit (0);
}

##############3##################

#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
int N=MAX;
double arrayA[MAX];
double arrayB[MAX];

double product(double* a, double* b, int N) 
{ int i=0;
  double sum = 0.0;
#pragma omp parallel for shared(sum)
   for(i=0; i<N; i++) {
     sum += a[i] * b[i];
   }
  return sum;
}

int main()
{ int i=0;
  double f=0.0; 
  for (i=0;i<N;i++)
      { arrayA[i]=  i;
        arrayB[i]=2*i;
      }
  f=product(arrayA,arrayB,N);
  printf(" result: %f\n",f);  
exit (0);
}

###############4########################

#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
int N=MAX;
double arrayA[MAX];
double arrayB[MAX];

double product(double* a, double* b, int N) 
{ int i=0;
  double sum = 0.0;
#pragma omp parallel for shared(sum)
   for(i=0; i<N; i++) {
#pragma omp critical
   sum += a[i] * b[i];
   }
  return sum;
}

int main()
{ int i=0;
  double f=0.0; 
  for (i=0;i<N;i++)
      { arrayA[i]=  i;
        arrayB[i]=2*i;
      }
  f=product(arrayA,arrayB,N);
  printf(" result: %f\n",f);  
exit (0);
}

################5#########################

#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
int N=MAX;
double arrayA[MAX];
double arrayB[MAX];

double product(double* a, double* b, int N) 
{ int i=0;
  double sum = 0.0;
#pragma omp parallel for reduction(+:sum)
   for(i=0; i<N; i++) {
      sum += a[i] * b[i];
   }
  return sum;
}

int main()
{ int i=0;
  double f=0.0; 
  for (i=0;i<N;i++)
      { arrayA[i]=  i;
        arrayB[i]=2*i;
      }
  f=product(arrayA,arrayB,N);
  printf(" result: %f\n",f);  
exit (0);
}

####################6###################3

#include <stdlib.h>
#include <stdio.h>

#define start 100000001
#define end  1000000000
 
int testForPrime(long p)  //slow prime test 
{ long i=0;
  for(i=2; i<p; i++) {
      if ((p%i)==0) return 0;
   }
  return 1;
}

int main(char **argv,int argc)
{ long i=0;
  int gPrimesFound=0;
#pragma omp parallel for schedule (dynamic, 10)
  for (i = start; i <= end; i +=2)
     { if (testForPrime(i))
          gPrimesFound++;
     }
   printf("number of primes between %d and %d: %d\n",start,end,gPrimesFound);
}

###################7############################

#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int i;
int node,numnodes;

int main(char **argv,int argc)
{ MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&node);
  MPI_Comm_size(MPI_COMM_WORLD,&numnodes);

#pragma omp parallel
  printf(" I am thread %d of %d threads inside process %d of %d\   
          processors\n",omp_get_thread_num(),omp_get_num_threads(),node,numnodes);

  MPI_Finalize();
}

#####################8#####################
