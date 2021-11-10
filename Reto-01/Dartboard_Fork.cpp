#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <random>
#include <unistd.h>
using namespace std::chrono;

using namespace std;

// n -> es el numero de lanzamientos
// hits -> numero de golpes

int main(int argc, char const *argv[]){

    long k, n, hits = 0;
    const double factor = 1.0 / RAND_MAX;

    int numHijos = atoi(argv[2]);

    int fd[2 * numHijos];
    
    pid_t pidC;
    
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

            std::uniform_real_distribution<double> dist(0, 1);
            
            for (k = hits = 0; k < n/numHijos; ++k)
            {
                double x = dist(mt);
                double y = dist(mt);
                if (x * x + y * y < 1.0) // Está dentro del circulo?
                    ++hits;
            }

            close (fd[2*i]);
            write(fd[2*i + 1], &hits, sizeof(hits));
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
            hits += aux;
        }

        auto stop = high_resolution_clock::now();

        std::chrono::duration<double> duration = stop - start;

        cout << duration.count();

        double pi_approx = 4.0 * hits / n;
    }

    return 0;
}