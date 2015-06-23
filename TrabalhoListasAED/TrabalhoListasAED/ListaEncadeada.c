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
	ListBubbleSort(head);
	PrintList();
	getchar();
}