#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

static Node *pushList(Node *head, long value);
static void printNode(Node *node);
static void destroyList(List *list);
static long determineSequence(int Size);
static List *createSublist(long);
static Node *list_pop(Node **list);
static void enQueue(Node *node, List *subList);
static void printList(List *listNode);

long *Load_Into_Array(char *Filename, int *Size)
{
	FILE *inptr;
	inptr = fopen(Filename, "rb");
	if (inptr == NULL)
	{
		fprintf(stderr, "Error: Could not open binary file.");
		return NULL;
	}
	
	long numBytes;
	fseek(inptr, 0L, SEEK_END);
	numBytes = ftell(inptr);
	(*Size) = numBytes / sizeof(long);
	long *array;
	array = (long *)malloc((*Size) * sizeof(long));
	if (array == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for array");
		fclose(inptr);
		return NULL;
	}
	//1 byte = 8 bits
	//long = 8 bytes/64 bits
	//unsinged =  4 bytes
	//Size of long because Im reading a long each time
	fseek(inptr, 0L, SEEK_SET);
	fread(array, sizeof(long), (*Size), inptr);
	fclose(inptr);
	return array;
}

int Save_From_Array(char *Filename, long *Array, int Size)
{
	FILE *outptr;
	outptr = fopen(Filename, "wb");
	if (outptr == NULL)
	{
		fprintf(stderr, "Error: Could not open outfile %s", Filename);
		return 0;
	}
		
	int written;		//Number of long int successfully saved into file
	written = fwrite(Array, sizeof(long), Size, outptr);
	fclose(outptr);
	return written;	
}

void Shell_Sort_Array(long *Array, int Size, double *N_Cmp)
{
	long sequence;
	sequence = determineSequence(Size);
	int lcv;
	int lcv2;
	long temp;
		
	for(sequence; sequence >= 1; sequence = (sequence - 1) / 3)
	{
		for(lcv = sequence; lcv < Size; lcv++)
		{
			temp = Array[lcv];
			lcv2 = lcv;
			while(lcv2 >= sequence && Array[lcv2 - sequence] > temp)
			{
				Array[lcv2] = Array[lcv2 - sequence];
				lcv2 -= sequence;
				(*N_Cmp)++;
			}
			Array[lcv2] = temp;
		} 
	}
}


///////////////////////////////////////////////////////////////////////////
///////////////////////LINKED LIST IMPLEMENETATION/////////////////////////
///////////////////////////////////////////////////////////////////////////

Node *Load_Into_List(char *Filename)
{
	FILE *inptr;
	Node *head;
	head = NULL;
	inptr = fopen(Filename, "rb");
	if (inptr == NULL)
	{
		fprintf(stderr, "Error: Could not open binary file.");
		return NULL;
	}
	long value;
	while(fread(&value, sizeof(long), 1, inptr))
	{
		head = pushList(head, value);
	}
	fclose(inptr);
	return head;
}

int Save_From_List(char *Filename, Node *list)
{
	FILE *outptr;
	outptr = fopen(Filename, "wb");
	if (outptr == NULL)
	{
		fprintf(stderr, "Error: Could not open outfile %s", Filename);
		return 0;
	}
	int dataWritten;
	dataWritten = 0;
	while(list != NULL)
	{
		fwrite(&(list -> value), sizeof(long), 1, outptr);
		list = list -> next;
		dataWritten++;
	}
	fclose(outptr);
	return dataWritten;	
}

Node *Shell_Sort_List(Node *list, double *N_Cmp)
{
	int Size;
	Size = 0;
	Node *start;
	start = list;
	while(list != NULL)
	{
		list = list -> next;
		Size++;
	}	
	long sequence;
	sequence = determineSequence(Size);
	long linkCounter;
	linkCounter = 0;
	List *listNode;
	List *listNode1;
	listNode = NULL;
	listNode1 = NULL;
	Node *node;
	node = NULL;
	list = start;
	printNode(list);
	for(sequence; sequence >= 1; sequence = (sequence -1) / 3)
	{
		listNode = createSublist(sequence);
		//l = listNode;
		while(list != NULL)
		{
			node = list_pop(&list);
			enQueue(node, listNode);
			listNode = listNode -> next;
		}
		//while(listNode != NULL) //&& listNode -> next -> node != NULL)
		//{
			/*node = list_pop(&listNode -> node);
			if(node != NULL)
			
			if(list == NULL)
			{
				node -> next = NULL;
				list = node;
			}
			node -> next = list;
			list = node;*/
			//listNode = listNode -> next;
		//}
		destroyList(listNode);
	}	
	/*while(list != NULL)
	{
		node = list_pop(&list);
		enQueue(node, listNode);
		listNode = listNode -> next;
	}
	
	printList(listNode);
	sequence = (sequence - 1) / 3;
	if(sequence >= 1)
	{
		listNode1 = createSublist(sequence);
	}
	for(sequence; sequence >= 1; sequence = (sequence - 1) / 3)
	{
		while(listNode -> node != NULL)
		{
			node = list_pop(&listNode -> node);
			enQueue(node, listNode1);
			listNode1 = listNode1 -> next;
		}
		printf("\n");
		printList(listNode1);	
	}*/
	//while(list != NULL)
		//{
			//listNode = createSublist(sequence);
			//node = list_pop(&list);
			//enQueue(node, listNode);
		//}
		//Create sublist 
		//then pop items
		//pq then unto list;
		//list = start;
		//While the main list is not empty
		//pop item off main list and pq it to one of the sublists
		//then pop items off the sublist into another set of sublists
		//do this until sequence is equal to 1
		//then eq everything back into the orignal list
		//destroyList(listNode);
	return list;
}

Node *pushList(Node *head, long value) //List)
{
	Node *node;
	node = (Node *)malloc(sizeof(Node));
	if(node == NULL)
	{
		fprintf(stderr, "Could not allcate memory for node");
		return NULL;
	}
	node -> value = value;
	node -> next = head;
	
	return node;
}

long determineSequence(int Size)
{
	long sequence;
	sequence = 0;
	while(((sequence * 3) + 1) < Size)
	{
		sequence =  (sequence * 3) + 1;
	}
	
	return sequence;
}

void printNode(Node *listNode)
{	
	while(listNode != NULL)
	{
		printf("%ld ", listNode -> value);
		listNode = listNode -> next;
	}
}

List *createSublist(long sequence)
{
	List *listNode;
	listNode = (List *)malloc(sizeof(List));
	if(listNode == NULL)
	{
		fprintf(stderr, "Could not allocate start of subList");
		return NULL;
	}
	List *head;
	head = listNode;
	listNode -> node = NULL;
	listNode -> next = NULL;
	for(int i = 1; i < sequence; i++)
	{
		List *subList;
		subList = (List *)malloc(sizeof(List));	
		if(subList == NULL)
		{
			fprintf(stderr, "Could ot allocate memory for sublist");
			return NULL;
		}
		subList -> node = NULL;
		subList -> next = listNode;
		listNode = subList;
	}
	head -> next = listNode;
	return listNode;
}

void destroyList(List *listNode)
{
	List *head;
	List* tail;
	head = listNode -> next;
	tail = listNode;
	tail -> next = NULL;
	listNode = head;
	
	List *current;
	while(listNode != NULL)
	{
		current = listNode;
		listNode = listNode -> next;
		free(current);
	}
}

Node *list_pop(Node **list)
{
	if(*list == NULL)
	{
		return NULL;
	}
	Node *head;
	Node * current;
	
	head = *list;
	current = head;
	head = head -> next;
	*list = head;
	current -> next = NULL;

	return current;
}

void enQueue(Node *node, List *subList)
{
	Node *prev;
	Node *current;
	if((subList -> node == NULL) || (node -> value <= subList -> node -> value))
	{
		node -> next = subList -> node;
		subList -> node = node;	
	}
	else
	{
		prev = subList -> node;
		current = subList -> node ->next;
		while(current != NULL && node -> value > current -> value)
		{
			prev = current;
			current = current -> next;
		}
		node -> next = current;
		prev -> next = node;
	}
}

void printList(List *listNode)
{
	List *head;
	List* tail;
	head = listNode -> next;
	tail = listNode;
	tail -> next = NULL;
	listNode = head;
	
	while(listNode != NULL)
	{
		printNode(listNode -> node);
		listNode = listNode -> next;
	}
}
