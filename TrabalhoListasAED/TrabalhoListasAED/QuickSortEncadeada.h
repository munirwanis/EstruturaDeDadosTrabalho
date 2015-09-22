#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct NoJorge
{
	int val;
	struct No *next, *prev;

}No;

No * UltimoNo(No *raiz);

No* Particao(No *inicio, No *fim);

void troca(int* x, int* y);

void ChamadaRecursivaQuickSort(No * inicio, No *fim);

void QuickSortEncadeada(No *inicio);

void ImprimeLista(No *inicio);

void InsereElemento(No ** inicio_ref, int valor);

void ListaEncadeadaQuick();