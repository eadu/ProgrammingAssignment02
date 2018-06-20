#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

static void destroyNode(Node *node);

int main(int argc, char *argv[])
{	
	if(strcmp(argv[1], "-a") == 0)
	{
		int Size;
		long *Array;
		int numLong;
		double N_Cmp;
		clock_t start;
		clock_t stop;
		
		start = clock();
		N_Cmp = 0;
		Size = 0;
		Array = Load_Into_Array(argv[2], &Size);
		printf("%d", Size);
		numLong = Save_From_Array(argv[3], Array, Size);	
		if (numLong != Size)
		{
			fprintf(stderr, "Could not write to file");
			return EXIT_FAILURE;
		}
		stop = clock();
		clock_t sortStart;
		clock_t sortStop;
		sortStart = clock();
		Shell_Sort_Array(Array, Size, &N_Cmp);
		sortStop = clock();
		//fprintf(stderr, "%.1f\n", N_Cmp);
		int i;
		for(i = 0; i < Size; i++)
		{
			printf("%ld ", Array[i]);
		}
		free(Array);
		fprintf(stdout, "\nI/O time: %le", (double)(stop - start) / CLOCKS_PER_SEC);
		fprintf(stdout, "\nSorting time: %le", (double)(sortStop - sortStart) / CLOCKS_PER_SEC);
		fprintf(stdout, "\nNumber of comparisons: %.0f", N_Cmp);
	}
	else if (strcmp(argv[1], "-l") == 0)
	{
		Node *list;
		list = NULL;
		double N_Cmp;
		N_Cmp = 0;
		list = Load_Into_List(argv[2]);
		int written;
		written = Save_From_List(argv[3], list);
		list = Shell_Sort_List(list, &N_Cmp);
		//printNode(head);
		destroyNode(list);
	}
	return EXIT_SUCCESS;
}
void destroyNode(Node *listNode)
{
	Node *current;
	while(listNode != NULL)
	{
		current = listNode;
		listNode = listNode -> next;
		free(current);
	}
}
