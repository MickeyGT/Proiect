#include"Library.h"

void merge(int vector[100000],int frst,int midl,int endg)
{
	int limit1, limit2;
	limit1 = midl - frst + 1;
	limit2 = endg - midl;
	for()
}

void merge_sort(int beg, int end, int vector[100000])
{
	int mid;
	if (beg < end)
		mid = (beg + end) / 2;
	merge(vector, beg, mid);
	merge(vector, mid, end);
	merge(vector, beg, mid, end);
	
}

void readarray(int n, int vector[100000])
{
	int i;
	for (i = 1;i <= n;i++)
		scanf("%d", vector[i]);
}

void printarray(int n, int vector[100000])
{
	int i;
	for (i = 1;i <= n;i++)
		printf("%d", vector[i]);

}
