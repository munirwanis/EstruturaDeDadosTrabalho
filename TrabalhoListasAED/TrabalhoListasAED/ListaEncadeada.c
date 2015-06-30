#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "ListaEncadeada.h"

item * current, *head = NULL;

// Cria a lista
item* CreateList(int val)
{
	item *ptr = (item *)malloc(sizeof(item));
	if (!ptr) { return NULL; }
	ptr->val = val;
	ptr->next = NULL;
	head = current = ptr;
	return ptr;

	while (current)
	{
		printf("%d\n", current->val);
		current = current->next;
	}
	getchar();
}

// Adiciona a lista encadeada um número inteiro
item* AddToList(int val)
{
	if (!head) 	{ return CreateList(val); }
	item *ptr = (item*)malloc(sizeof(item));
	if (!ptr) { return NULL; }
	ptr->val = val;
	ptr->next = NULL;
	current->next = ptr;
	current = ptr;
	return ptr;
}

// BubbleSort para lista encadeada
void ListBubbleSort(item *start)
{
	int swapped, i;
	item *ptr1 = start;
	item *lptr = NULL;

	/* Checking for empty list */
	if (ptr1 == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->val > ptr1->next->val)
			{
				i = ptr1->val;
				ptr1->val = ptr1->next->val;
				ptr1->next->val = i;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

// BucketSort para a lista encadeada
void BucketSortOrd(item *l)
{
	int i;

	item *lista = l;
	item *listaBucket = l;
	int vetor[MAX_TAM_VETOR];
	for (i = 0; i < MAX_TAM_VETOR; i++)
	{
		vetor[i] = lista->val;
		lista = lista->next;
	}
	BucketSort(vetor);

	for (i = 0; i < MAX_TAM_VETOR; i++)
	{
		listaBucket->val = vetor[i];
		listaBucket = listaBucket->next;
	}
}

// Printa a lista criada
void PrintList()
{
	item *ptr = head;
	printf("---- Linked List ----\n");
	while (ptr)
	{
		printf("[%d]\n", ptr->val);
		ptr = ptr->next;
	}
	printf("----End of Linked List----\n");
}

// Chama os métodos da Lista Encadeada
void ListaEncadeada()
{
	FILE *fp;

	clock_t start, end;
	double cpu_time_used;

	for (int i = 0; i < MAX_TAM_VETOR; i++)
	{
		AddToList(rand() % MAX_TAM_VETOR);
	}

	// Abro arquivo
	fp = fopen("ListaEncadeadaResult.txt", "a");
	fprintf(fp, "Quantidade de Numeros na lista: %d\nOrdenacao\tTempo\n", MAX_TAM_VETOR);

	// BubbleSort
	start = clock();
	ListBubbleSort(head);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nLista Encadeada:\nOrdenacao\tTempo\n");
	printf("BubbleSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "BubbleSort\t%.10f\n", cpu_time_used);

	// BucketSort
	start = clock();
	BucketSortOrd(head);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("BucketSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "BucketSort\t%.10f\n", cpu_time_used);

	fclose(fp);
}