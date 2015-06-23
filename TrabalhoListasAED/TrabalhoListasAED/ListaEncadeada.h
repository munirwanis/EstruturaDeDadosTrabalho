#ifndef NUM_MAX_LISTA
#define NUM_MAX_LISTA 10
#endif

typedef struct No
{
	int val;
	struct No * next;
}item;
item* CreateList(int val);
item* AddToList(int val);
void ListBubbleSort(item *start);
void LinkedListTest();
void PrintList();