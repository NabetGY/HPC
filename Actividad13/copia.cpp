#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>
#include <ctime>

using namespace std;

void pedirDatos();
void mostrarMatriz(double **,int);

void mult(int n, double **a, double **b, double **c){

	omp_set_num_threads(4);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int numeroDeHilos = omp_get_num_threads();
		int tamanio = (int) n / numeroDeHilos;
		int inicio = id * tamanio;
		int fin = inicio + tamanio;

		for (int i=0; i<n; i++){ 
			for (int j=inicio; j<fin; j++){
				c[i][j] = 0.0; 
				for (int k=0; k<n; k++){
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
				}
				//cout<<"\n"<<*(*(c+i)+j)<<" numero de hilo: "<< id;
			}
		}
	}

}

double **a,**b,**c;
int n;

unsigned t0, t1;

int main(){

t0=clock();

   pedirDatos();
   mult(n,a,b,c);
  //mostrarMatriz(c,n);

   t1 = clock();
 
double time = (double(t1-t0)/CLOCKS_PER_SEC);
cout << "Execution Time: " << time << endl;
   
}


void pedirDatos(){
	cout<<"Digite el numero de la matriz n : ";
	cin>>n;

	
	//Reservar memoria para la primera matriz
	a = new double*[n]; //Reservar memoria para las filas
	for(int i=0;i<n;i++){
		a[i] = new double[n]; //Reservar memoria para las columnas
	}
	
	cout<<"\nDigitando los elementos de la primera matriz: \n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			
			*(*(a+i)+j) = 5; //a[i][j]
		//	mostrarMatriz(a,n);
		}
	}
	
	//Reservar memoria para la segunda matriz
	b = new double*[n]; //Reservar memoria para las filas
	for(int i=0;i<n;i++){
		b[i] = new double[n]; //Reservar memoria para las columnas
	}
	
	cout<<"\nDigitando los elementos de la segunda matriz: \n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
		//	cout<<"Digite un numero["<<i<<"]["<<j<<"]: ";
			*(*(b+i)+j)=5; //a[i][j]
		}
	}
	
	c = new double*[n]; //Reservar memoria para las filas
	for(int i=0;i<n;i++){
		c[i] = new double[n]; //Reservar memoria para las columnas
	}
	
}

void mostrarMatriz(double **c,int n){
	cout<<"\nLa matriz resultante es: \n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<*(*(c+i)+j)<<" ";
		}
		cout<<"\n";
	}
}


