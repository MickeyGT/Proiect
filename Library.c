#include"Library.h"
#include<stdio.h>
#include<stdlib.h>
void MergeSort(float vector[100000],int beg,int end,float B[100000])
{
	if (end - beg <= 1)                      
		return;                                											
	int mid = (end + beg) / 2;              
	MergeSort(vector, beg, mid,B);
	MergeSort(vector, mid, end,B);
	MergeParts(vector, beg, mid, end,B);
	for (int k = beg;k < end;k++)
		vector[k] = B[k];							          
}


void AddtoHeap(struct node *root, int value)
{
	if (value < root->data)
	{
		if (root->left == NULL)
		{
			struct node *n;
			n = (struct node*)malloc(sizeof(struct node));
			n->data = value;
			n->left = NULL;
			n->right = NULL;
			root->left = n;
		}
		else
			AddtoHeap(root->left, value);
	}
	else
	{
		if (root->right == NULL)
		{
			struct node *n;
			n = (struct node*)malloc(sizeof(struct node));
			n->data = value;
			n->left = NULL;
			n->right = NULL;
			root->right = n;
		}
		else
			AddtoHeap(root->right, value);
	}
}

void HeapSort(struct node *root)
{
	if (root->left != NULL)
		HeapSort(root->left);
	printf("%d ", root->data);
	if (root->right != NULL)
		HeapSort(root->right);
}

void ConstructHeap(int n,struct node *root)
{
	int el;
	for (int i = 1;i <= n-1;i++)
	{
		scanf("%d", &el);
		AddtoHeap(root, el);
	}
}


void MergeParts(float A[100000],int beg,int mid,int end,float B[100000])
{
	int ind1, ind2;
	//float B[100000];
	ind1 = beg;
	ind2 = mid;
	for (int k = beg; k < end; k++)
	{
		if ((ind1 < mid) && ((ind2 >= end)|| (A[ind1] <= A[ind2])))
		{
			B[k] = A[ind1];
			ind1 = ind1 + 1;
		}
		else 
		{
			B[k] = A[ind2];
			ind2 = ind2 + 1;
		}
	}

}

void readarray(int n, float vector[100000])
{
	int i;
	for (i = 1;i <= n;i++)
		scanf("%f", &vector[i]);
}

void printarray(int n, float vector[100000])
{
	int i;
	for (i = 1;i <= n;i++)
		printf("%f ", vector[i]);
	printf("\n");

}

