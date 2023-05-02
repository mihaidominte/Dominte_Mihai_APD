#include "stdio.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace std::chrono;

void numGenerator(int sir[], int dimensiune);
void bubbleSort(int sir[], int dimensiune);
void afisare(int sir[], int dimensiune);

int main() {

	int dimensiune, optiune;

	printf("Introduceti dimensiunea:");
	scanf_s("%d", &dimensiune);

	int* sir = (int*)malloc(dimensiune * sizeof(int));

	numGenerator(sir, dimensiune);
	printf("Generare finalizata \n");

	auto start = high_resolution_clock::now();
	bubbleSort(sir, dimensiune);
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

void bubbleSort(int sir[], int dimensiune) {
	for (int i = 0; i < dimensiune - 1; i++) {
		for (int j = 0; j < dimensiune - i - 1; j++) {
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