#include <time.h>
#ifndef MAX_TAM_VETOR
#define MAX_TAM_VETOR 10000
#endif

typedef struct No
{
	int val;
	struct No * next;
}item;

item* CreateList(int val);

item* AddToList(int val);

void ListBubbleSort(item *start);

void BucketSortOrd(item *l);

void ListaEncadeada();

void PrintList();