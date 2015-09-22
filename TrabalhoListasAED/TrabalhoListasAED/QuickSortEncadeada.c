#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "ListaEncadeada.h"

typedef struct NoJorge
{
	int val;
	struct No *next, *prev;

}No;

void troca(int* x, int* y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

No *UltimoNo(No *raiz)
{
	while (raiz && raiz->next)
		raiz = raiz->next;
	return raiz;
}

No* Particao(No *inicio, No *fim)
{
	int x = fim->val;
	No *i = inicio->prev;
	No *j;
	for (j = inicio; j != fim; j = j->next)
	{
		if (j->val <= x)
		{
			i = (i == NULL) ? inicio : i->next;
			troca(&(i->val), &(j->val));
		}
	}
	i = (i == NULL) ? inicio : i->next;
	troca(&(i->val), &(fim->val));
	return i;
}

void ChamadaRecursivaQuickSort(No * inicio, No *fim)
{
	if (inicio != NULL && inicio != fim && inicio != fim->next)
	{
		No *p = Particao(inicio, fim);
		ChamadaRecursivaQuickSort(inicio, p->prev);
		ChamadaRecursivaQuickSort(p->next, fim);
	}
}

void QuickSortEncadeada(No *inicio)
{
	No *fim = UltimoNo(inicio);
	ChamadaRecursivaQuickSort(inicio, fim);
}

void ImprimeLista(No *inicio)
{
	while (inicio)
	{
		printf("%d\t", inicio->val);
		inicio = inicio->next;
	}
	printf("\n");
}

void InsereElemento(No ** inicio_ref, int valor)
{
	No* novo_no = (No *)malloc(sizeof(No));
	novo_no->val = valor;

	novo_no->prev = NULL;
	novo_no->next = (*inicio_ref);

	if ((*inicio_ref) != NULL)  (*inicio_ref)->prev = novo_no;

	(*inicio_ref) = novo_no;
}

void ListaEncadeadaQuick()
{

	FILE *fp;

	clock_t start, end;
	double cpu_time_used;

	struct node *a = NULL;
	int i;

	for (i = 0; i < MAX_TAM_VETOR; i++)
	{
		InsereElemento(&a, rand() % MAX_TAM_VETOR);
	}

	//ImprimeLista(a);

	start = clock();
	QuickSortEncadeada(a);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fp = fopen("ListaEncadeadaQuick.csv", "a");
	fprintf(fp, "%.10f;%d\n", cpu_time_used, MAX_TAM_VETOR);
	fclose(fp);
	/*printf("QuickSort\t%.10f\n", cpu_time_used);
	fprintf(fp, "QucikSort\t%.10f\n", cpu_time_used);*/

	//ImprimeLista(a);
}