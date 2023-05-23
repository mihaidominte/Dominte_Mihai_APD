#include "stdio.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

void numGenerator(int sir[], int dimensiune);
void bubbleSort(int sir[], int dimensiune, int nr_thread);
void afisare(int sir[], int dimensiune);

int main() {
	vector<thread> sir_threads;
	int dimensiune, optiune;
	int nr_threads;

	printf("Introduceti dimensiunea:");
	scanf_s("%d", &dimensiune);
	printf("Introduceti numarul firelor de executie:");
	scanf_s("%d", &nr_threads);

	int* sir = (int*)malloc(dimensiune * sizeof(int));

	numGenerator(sir, dimensiune);
	printf("Generare finalizata \n");

	auto start = high_resolution_clock::now();
	for (int i = 0; i < nr_threads; i++) {
		sir_threads.emplace_back(bubbleSort, sir, dimensiune / nr_threads, i);
	}
	for (int i = 0; i < nr_threads; i++) {
		sir_threads[i].join();
	}
	bubbleSort(sir, dimensiune, 0);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Timpul de sortare: " << duration.count() << " microsecunde" << endl;
	printf("Afisati numerele sortate 1/0:");
	scanf_s("%d", &optiune);

	if (optiune == 1) {
		afisare(sir, dimensiune);
	}

	return 0;
}

void numGenerator(int sir[], int dimensiune) {
	srand(time(NULL));
	for (int i = 0; i < dimensiune; i++) {
		sir[i] = rand() * rand();
	}
}

void bubbleSort(int sir[], int dimensiune, int nr_thread) {
	int start = nr_thread * dimensiune;
	for (int i = start; i < start + dimensiune - 1; i++) {
		for (int j = start; j < start + dimensiune - i - 1; j++) {
			if (sir[j] > sir[j + 1]) {
				int temp = sir[j];
				sir[j] = sir[j + 1];
				sir[j + 1] = temp;
			}
		}
	}
}

void afisare(int sir[], int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("%d ", sir[i]);
	}
}