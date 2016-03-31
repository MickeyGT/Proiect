#include "Library.h"
#include<stdio.h>
#include<stdlib.h>

float v[100000],v1[100000];
int n,el;
int main()
{
	printf("N=");
	scanf("%i", &n);
	printf("Print %d elements:\n", n);
	struct node *root;
	root = (struct node*) malloc(sizeof(struct node));
	root->left = NULL;
	root->right = NULL;
	scanf("%d", &el);
	root->data = el;
	ConstructHeap(n,root);
	printf("The sorted elements from Heap:\n");
	HeapSort(root);
	printf("\n");
	system("pause");
	return 0;
}
