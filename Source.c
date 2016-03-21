#include "Library.h"
#include<stdio.h>
#include<stdlib.h>

float v[100000],v1[100000];
int n;
int main()
{
	scanf("%i", &n);
	readarray(n, v);
	printarray(n, v);
	MergeSort(v, 1, n+1,v1);
	printarray(n, v);
	system("pause");
	return 0;
}
