#include <time.h>

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