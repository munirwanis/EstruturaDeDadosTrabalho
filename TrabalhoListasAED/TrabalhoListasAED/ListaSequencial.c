#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ListaEncadeada.h"

// Inicializador do Vetor
void InicializaVetor(int vet[])
{
	for (int i = 0; i < MAX_TAM_VETOR; i++)
	{
		vet[i] = rand() % MAX_TAM_VETOR;
	}
}

// Função para imprimir o Vetor
void ImprimeVetor(int vet[])
{
	int i;
	for (i = 0; i < MAX_TAM_VETOR; i++)
	{
		printf("%d\t", vet[i]);
	}
}

// BubbleSort para a Lista Sequencial
void BubbleSort(int vet[], int tamanho)
{
	int troca;

	for (int i = 0; i < tamanho - 1; i++)
	{
		for (int j = 0; j < tamanho - i - 1; j++)
		{
			if (vet[j] > vet[j + 1])
			{
				troca = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = troca;
			}
		}
	}
}

// QuickSort para a Lista Sequencial
void QuickSort(int vet[], int inicio, int fim)
{
	int i, j, pivo, aux;
	i = inicio;
	j = fim;
	pivo = vet[(inicio + fim) / 2];

	while (i <= j)
	{
		while (vet[i] < pivo && i<fim){ i++; }
		while (vet[j]>pivo && j > inicio){ j--; }
		if (i <= j)
		{
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			i = i + 1; j = j - 1;
		}
	}
	if (j > inicio){ QuickSort(vet, inicio, j); }
	if (i < fim){ QuickSort(vet, i, fim); }
}

// BucketSort para a Lista Sequencial
void BucketSort(int vet[])
{
	int i, j;
	int count[MAX_TAM_VETOR];
	for (i = 0; i < MAX_TAM_VETOR; i++) {
		count[i] = 0;
	}
	for (i = 0; i < MAX_TAM_VETOR; i++) {
		(count[vet[i]])++;
	}
	for (i = 0, j = 0; i < MAX_TAM_VETOR; i++) {
		for (; count[i] > 0; (count[i])--) {
			vet[j++] = i;
		}
	}
}

// testes para ver se métodos funcionam
void ListaSequencial()
{
	int vetor[MAX_TAM_VETOR];

	FILE *fp;

	clock_t start, end;
	double cpu_time_used;

	// Sequencial BubbleSort
	InicializaVetor(vetor);
	start = clock();
	BubbleSort(vetor, MAX_TAM_VETOR);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fp = fopen("ListaSequencialBubble.csv", "a");
	fprintf(fp, "%.10f;%d\n", cpu_time_used, MAX_TAM_VETOR);
	fclose(fp);
	/*printf("\nLista Sequencial:\nOrdenacao\tTempo\n");
	printf("BubbleSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "BubbleSort\t%.10f\n", cpu_time_used);*/
	
	// Sequencial QuickSort
	InicializaVetor(vetor);
	start = clock();
	QuickSort(vetor, 0, MAX_TAM_VETOR - 1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fp = fopen("ListaSequencialQuick.csv", "a");
	fprintf(fp, "%.10f;%d\n", cpu_time_used, MAX_TAM_VETOR);
	fclose(fp);
	/*printf("QuickSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "QuickSort\t%.10f\n", cpu_time_used);*/
	
	// Sequencial BucketSort
	InicializaVetor(vetor);
	start = clock();
	BucketSort(vetor);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fp = fopen("ListaSequencialBucket.csv", "a");
	fprintf(fp, "%.10f;%d\n", cpu_time_used, MAX_TAM_VETOR);
	fclose(fp);
	/*printf("BucketSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "BucketSort\t%.10f\n", cpu_time_used);*/
}
