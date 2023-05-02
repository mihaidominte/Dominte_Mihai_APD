#include<iostream>
#include <chrono>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <random>
#include "mpi.h"
using namespace std;
using namespace std::chrono;
#define SIZE 200000

void numGenerator(uint32_t  sir[], int dimensiune);
void bubbleSort(uint32_t  array[], int size);
int main(int argc, char* argv[])
{
    mt19937 gen(random_device{}());
    int rank;
    int nrproc;
    int dimensiune;

    uint32_t  localArray[SIZE];
    uint32_t a[SIZE];
    ofstream MyFile("filename.txt");

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nrproc);

    if (rank == 0) {
        numGenerator(a, SIZE);
    }

    MPI_Scatter(a, SIZE/nrproc, MPI_INT, localArray, SIZE/nrproc, MPI_INT, 0, MPI_COMM_WORLD);
    srand(static_cast<unsigned int>(time(nullptr)));

    auto start = high_resolution_clock::now();

    bubbleSort(localArray, SIZE/nrproc);

    MPI_Gather(localArray, SIZE/nrproc, MPI_INT, a, SIZE/nrproc, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        bubbleSort(a, SIZE);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        for (int i = 0; i < SIZE; i++) {
            MyFile << i << ". " << a[i] << "\n";

        }
        cout << "Time taken by function: "
            << duration.count() << " microseconds" << endl;
    }

    MyFile.close();
    MPI_Finalize();
    exit(0);
}
void bubbleSort(uint32_t  sir[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sir[j] > sir[j + 1]) {
                int temp = sir[j];
                sir[j] = sir[j + 1];
                sir[j + 1] = temp;
            }
        }
    }

}
void numGenerator(uint32_t  sir[], int dimensiune) {
    srand(time(NULL));
    for (int i = 0; i < dimensiune; i++) {
        sir[i] = rand() * rand();
    }
}
