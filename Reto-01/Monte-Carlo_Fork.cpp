#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <random>
#include <unistd.h>
using namespace std::chrono;

using namespace std;

std::random_device rd;
std::mt19937 mt(rd());

int euclid(int u, int v){
    int r;
    while ((r = u % v) != 0){
        u = v;
        v= r;
    }
    return v;
}

int main (int argc, char const *argv[]){

    int numHijos = atoi(argv[2]);

    int fd[2 * numHijos];
    
    pid_t pidC;
        
    int n, nTries, nHits;
        
    n = atoi(argv[1]);

    auto start = high_resolution_clock::now();

    for (int i = 0; i < numHijos; i++){
        pipe(&fd[2*i]);
        pidC = fork();
        if (pidC == 0){
            if (n <= 0)
                return 0;

            std::random_device rd;
            std::mt19937 mt(rd());

            std::uniform_real_distribution<double> dist(0, RAND_MAX);

            for (nTries = nHits=0; nTries <n/numHijos; ++nTries){
                int A = dist(mt) + 1;
                int C = dist(mt) + 1;
                if (euclid(A, C) == 1) // A and C are relative prin
                    ++nHits;
            }
            
            close (fd[2*i]);
            write(fd[2*i + 1], &nHits, sizeof(nHits));
            close(fd[2*i + 1]);
            exit(0);
        }
    }

     if (pidC > 0){  
        for (int i = 0; i < numHijos; i++){
            int aux = 0;
            close (fd[2*i + 1]);
            read(fd[2*i], &aux, sizeof(aux));
            close(fd[2*i]);
            nHits += aux;
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        cout <<duration.count();

        double f = nHits * 1.0/n;
        double pi = sqrt(6.0/ f);

        cout << "\npi: " << pi << endl;
        
    }
    return 0;
}

