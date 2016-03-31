#ifndef Library
#define Library
struct node
{
	int data;
	struct note *right;
	struct node *left;
};
void HeapSort(struct node* root);

void ConstructHeap(int n, struct node *root);

void AddtoHeap(struct node *root, int value);

void MergeSort(float vector[100000], int beg, int end,float B[100000]);

void MergeParts(float A[100000], int beg, int mid, int end, float B[100000]);

void readarray(int n, float vector[100000]);

void printarray(int n, float vector[100000]);
#endif
