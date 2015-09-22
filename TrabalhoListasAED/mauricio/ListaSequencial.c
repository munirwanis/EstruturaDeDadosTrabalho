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

    typedef struct 
	{
         int quantidade;
         int balde[tam_bucket];
    }bucket;
    
	int i, j,k;
	
	bucket BucketList[num_balde];
	
    for(i=0;i<num_balde;i++)                 //Colocar 0 em todas variavel quantidade
    {
        BucketList[i].quantidade=0;
    } 
    for(i=0;i<MAX_TAM_VETOR;i++) // Percorrer o vetor todo
    {
        j=(num_balde)-1;    //Para saber a quantidade do balde
        while(j>=0)     
        {
            if(vet[i] >= (j*10)) // Verifica a posicao a se inserida
            {
                BucketList[j].balde[BucketList[j].quantidade]=vet[i]; // colocar o elemento na posicao referente a ele pela a quantidade
                (BucketList[j].quantidade)++;       // incrmenta a quantidade
                break;
            }     
            j--;    //Diminui a possibilidade da posica a ser inserido 
        }
    
    }
        
    for(i=0;i<num_balde;i++)   //Ordena chamando outro metodo
    {
        if(BucketList[i].quantidade > 0)
        {
            BubbleSort(BucketList[i].balde,BucketList[i].quantidade);
        
        }     
    }                  
    i=0;
   
    for(j=0;j <num_balde; j++) // Os elementos sao inserido no vetor
    {                  
        for(k=0;k < BucketList[j].quantidade;k++)
        {
            vet[i]=BucketList[j].balde[k];
            i++;
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

	fp = fopen("ListaSequencialResult.txt", "a");
	fprintf(fp, "Quantidade de Numeros na lista: %d\nOrdenacao\tTempo\n", MAX_TAM_VETOR);
    
	// Sequencial BubbleSort
	InicializaVetor(vetor);
	start = clock();
	BubbleSort(vetor, MAX_TAM_VETOR);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nLista Sequencial:\nOrdenacao\tTempo\n");
	printf("BubbleSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "BubbleSort\t%.10f\n", cpu_time_used);
	
	// Sequencial QuickSort
	InicializaVetor(vetor);
	start = clock();
	QuickSort(vetor, 0, MAX_TAM_VETOR - 1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("QuickSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "QuickSort\t%.10f\n", cpu_time_used);
	
	
	printf("Oi");
	// Sequencial BucketSort
	InicializaVetor(vetor);
	start = clock();
	printf("Oi");
	BucketSort(vetor);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("BucketSort2\t%.10f\n", cpu_time_used);
	fprintf(fp, "BucketSort\t%.10f\n", cpu_time_used);
	
	fclose(fp);
	getchar();
}
