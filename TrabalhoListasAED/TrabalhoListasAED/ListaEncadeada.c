#include<stdio.h>
#include<stdlib.h>
#include "BubbleSort.h"
#ifndef NUM_MAX_LISTA
#define NUM_MAX_LISTA 10
#endif


typedef struct No
{
	int val;
	struct No * next;
}item;

item * current, *head = NULL;

item* CreateList(int val)
{
	item *ptr = (item *)malloc(sizeof(item));
	if (!ptr) { return NULL; }
	ptr->val = val;
	ptr->next = NULL;
	head = current = ptr;
	return ptr;

	//for (int i = 1; i <= NUM_MAX_LISTA; i++)
	//{
	//	current = (item *)malloc(sizeof(item));
	//	current->val = i/*rand(NUM_MAX_LISTA)*/;
	//	current->next = head;
	//	head = current;
	//}
	//current = head;

	while (current)
	{
		printf("%d\n", current->val);
		current = current->next;
	}
	getchar();
}

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

void ListBubbleSort(item **head)
{
	int done = 0;
	//if (*head == NULL || (*head)->next == NULL) return;

	while (!done)
	{
		item **ptrSource = head; // "source" of the ptr to the current node in the list struct
		item *ptrLocalIterator = *head; // local iterator pointer
		item *ptrNext = (*head)->next; // local next pointer
		done = 1;
		while (ptrNext)
		{
			if (ptrLocalIterator->val > ptrNext->val)
			{
				ptrLocalIterator->next = ptrNext->next;
				ptrNext->next = ptrLocalIterator;
				*ptrSource = ptrNext;
				done = 0;
			}
			ptrSource = &ptrLocalIterator->next;
			ptrLocalIterator = ptrNext;
			ptrNext = ptrNext->next;
		}
	}
}

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

void LinkedListTest()
{
	for (int i = 0; i < NUM_MAX_LISTA; i++)
	{
		AddToList(rand() % NUM_MAX_LISTA);
	}
	PrintList();
	item *ptr = head;
	ListBubbleSort(ptr);
	PrintList();
	getchar();
}