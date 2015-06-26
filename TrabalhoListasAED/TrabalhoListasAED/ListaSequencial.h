#include <time.h>
#ifndef MAX_TAM_VETOR
#define MAX_TAM_VETOR 100000
#endif

void InicializaVetor(int *vet[]);

void imprimeVetor(int *vet[]);

void BubbleSort(int *vet[], int tamanho);

void QuickSort(int *vet[], int inicio, int fim);

void SequencialTest();