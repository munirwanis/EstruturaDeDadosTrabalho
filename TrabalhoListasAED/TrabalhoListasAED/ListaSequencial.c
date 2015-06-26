#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef MAX_TAM_VETOR
#define MAX_TAM_VETOR 100000
#endif

// EDITADO POR MUNIR
void InicializaVetor(int *vet[])
{
	for (int i = 0; i < MAX_TAM_VETOR; i++)
	{
		vet[i] = rand() % MAX_TAM_VETOR;
	}
}

void ImprimeVetor(int *vet[])
{
	int i;
	for (i = 0; i < MAX_TAM_VETOR; i++)
	{
		printf("%d\t", *(vet + i));
	}
}

// PRECISO
void BubbleSort(int *vet[], int tamanho)
{
	int *temp, x, troca = 1, passos = 0;

	while (troca != 0 && tamanho > 0)
	{
		for (x = 0; x<tamanho - 1; x++)
		{
			//++passos;
			troca = 0;
			if (vet[x]>vet[x + 1])
			{
				temp = vet[x];
				vet[x] = vet[x + 1];
				vet[x + 1] = temp;
				troca = 1;
			}
		}
		--tamanho;
	}
	//printf("\nBubbleSort (passos): %d\n",passos);
}

// PRECISO 
void QuickSort(int *vet[], int inicio, int fim)
{
	int i, j, *pivo, *aux;
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

// testes para ver se métodos funcionam
void SequencialTest()
{
	int *vetor[MAX_TAM_VETOR];

	clock_t start, end;
	double cpu_time_used;

	InicializaVetor(vetor);

	start = clock();
	BubbleSort(vetor, MAX_TAM_VETOR);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nOrdenacao\tTempo\n");
	printf("BubbleSort\t%.10f\n", cpu_time_used);
	getchar();

	InicializaVetor(vetor);
	start = clock();
	QuickSort(vetor, 0, MAX_TAM_VETOR - 1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nOrdenacao\tTempo\n");
	printf("QuickSort\t%.10f\n", cpu_time_used);

	getchar();
}
