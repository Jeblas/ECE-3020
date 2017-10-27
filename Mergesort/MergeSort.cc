// Merge/MergeSort functions sourced from https://gist.github.com/Genieliu/1542735

#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

void Merge(int* A,int,int,int);
void MergeSort(int* A,int p,int r);

int main()
{
    // Initialize random seed
    srand(time(NULL));
    std::ofstream outFile;
    outFile.open("MergeSort.csv", std::ios::app);
    std::vector<unsigned long long int> timeTaken;
    int * arrayToSort;

    //create arrays
    for (int i = 10000; i <=100000; i+=10000) {
        arrayToSort = new int[i];

        for (int j = 0; j <= i; ++j) {
            //choose random number from -100 to 100
            arrayToSort[j] = rand() % 201 - 100;
        }
        
        // start timer
        auto t1 = std::chrono::high_resolution_clock::now();
        // sort
        MergeSort(arrayToSort, 0, i - 1);
        // end timer
        auto t2 = std::chrono::high_resolution_clock::now();
        timeTaken.push_back(std::chrono::duration_cast<
                std::chrono::microseconds>(t2 - t1).count());

        delete [] arrayToSort;
    }

    outFile << "Size,Time(us)\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << (i + 1) * 10000 << " : " << timeTaken[i] << std::endl;
        outFile << (i + 1) * 10000 << "," << timeTaken[i] << "\n";
    }
    outFile.close();

    return 0;
}
void Merge(int* A,int p,int q,int r) {
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1];
    int R[n2+1];
    for(int i=0; i<n1; i++) L[i]=A[p+i];
    for(int j=0; j<n2; j++) R[j]=A[q+1+j];
    int i=0;
    int j=0;
    int n=0;
    while(i!=n1 && j!=n2) {
        if(L[i]>R[j]) {
            A[p+n]=R[j];
            j++;
        } else {
            A[p+n]=L[i];
            i++;
        }
        n++;
    }
    while(j!=n2) {
        A[p+n]=R[j];
        j++;
        n++;
    }
    while(i!=n1) {
        A[p+n]=L[i];
        i++;
        n++;
    }
}
void MergeSort(int* A,int p,int r) {
    if(r>p) {
        int q;
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
