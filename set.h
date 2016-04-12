#ifndef SET_H
#define SET_H

/*
  The set is represented using a red-black tree which guarantees deletion,insertion and searching in
  O(log(n)).Elements are unique.
*/


//Node of the red-black tree which has a color,a value,the left,right child and the parent
struct set_node
{
	int color;
	void *value;

	struct set_node *left, *right,*parent;
};

//color values in te set_node
#define BLACK 0
#define RED 1

typedef struct set_node set_node;


//Initializing the set
void set_init(set_node **set);

//Inserting an element in the set based on a custom defined comparation function
void set_insert(set_node **set, void *elem, int size, int(*cmp)(const void*, const void*));

//Deleting an element in the set based on a custom defined comparation function
void set_delete(set_node *set, void *elem, int size, int(*cmp)(const void*, const void*));

//Searching an element in the set based on a custom defined comparation function
int set_search(set_node *set, void *elem,int size, int(*cmp)(const void*, const void*));

//Sorts the data to a new buffer
void sort(set_node *root, void *dest, int size, int *n);


#endif