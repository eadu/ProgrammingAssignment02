#include <stdio.h>
#include <stdlib.h>


typedef struct _Node
{
	long value;
	struct _Node *next;
}Node;

typedef struct _List
{
	Node *node;
	struct _List *next;
}List;
//Function Declarations
long *Load_Into_Array(char *, int *);
int Save_From_Array(char *, long *, int);
void Shell_Sort_Array(long *, int, double *);
Node *Load_Into_List(char *);
int Save_From_List(char *, Node *);
Node *Shell_Sort_List(Node *, double *);
