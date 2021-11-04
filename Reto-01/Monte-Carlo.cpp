#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int euclid(int u, int v){
    int r;
    while ((r = u % v) != 0){
        u = v;
        v= r;
    }
    return v;
}

int main (void){
    while (1){
        int n, nTries, nHits;
        cout << "Enter no of tries (or 0 to exit): ";
        cin >>n; 
        if (n <= 0) break;
        srand((int) clock());

        for (nTries = nHits=0; nTries <n; ++nTries){
            int A = rand() + 1;
            int C = rand() + 1;
            if (euclid(A, C) == 1) // A and C are relative prin
                ++nHits;
        }

        double f = nHits * 1.0/nTries;
        double pi = sqrt(6.0/ f); 
        cout << "After " << nTries <<" tries is pi " << pi << endl;

    }

    return 0;
}

