#include <time.h>
#ifndef MAX_TAM_VETOR
#define MAX_TAM_VETOR 1000
#define num_balde 10

#define tam_bucket MAX_TAM_VETOR
#endif

typedef struct No
{
	int val;
	struct No * next;
}item;

item* CreateList(int val);

item* AddToList(int val);

void ListBubbleSort(item *start);

void ListaEncadeada();

void PrintList();
