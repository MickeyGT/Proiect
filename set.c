#include"set.h"
#include<string.h>
#include<stdio.h>


void set_init(set_node **set)
{
	*set = NULL;
}

void left_rotate(set_node **root, set_node *node)
{
	//Set z as the right child
	set_node *z = node->right;

	//Right child of node becomes the left child of the right child of the node
	node->right = z->left;

	//If the right child,now moved is not null it means that is has a parent and we must update it
	if (node->right != NULL)
		node->right->parent = node;

	//Update the parent of the initial right child of the node
	z->parent = node->parent;

	//Update the child of the parent of the initial node
	if (node->parent == NULL)
		(*root) = z;
	else if (node->parent->left == node)
		node->parent->left = z;
	else
		node->parent->right = z;

	//Update the child of the the right child of the initial node
	z->left = node;

	//Update the parent of the initial node
	node->parent = z;

}

void right_rotate(set_node **root, set_node *node)
{
	//Set z as the left child
	set_node *z = node->left;

	
	//Left child of node becomes the right child of the left child of the node
	node->left = z->right;

	//If the left child,now moved is not null it means that is has a parent and we must update it
	if (node->left != NULL)
		node->left->parent = node;
	
	//Update the parent of the initial left child of the node
	z->parent = node->parent;

	//Update the child of the parent of the initial node
	if (node->parent == NULL)
		(*root) = z;
	else if (node->parent->left == node)
		node->parent->left = z;
	else
		node->parent->right = z;
	
	//Update the child of the the left child of the initial node
	z->right = node;

	//Update the parent of the initial node
	node->parent = z;

}

void set_insert(set_node **root, void *elem,int size, int (*cmp)(const void*, const void*))
{
	//If the set is empty then we will insert a node which is black
	if(*root == NULL)
	{
		(*root) = malloc(sizeof(set_node)); //Allocating size for the set

		(*root)->color = BLACK; //Setting the color black of the first node
		(*root)->value = malloc(size); //Allocating size for the value which needs to be stored
		
		memcpy((*root)->value, elem, size); //Copying the element into the node

		(*root)->left = (*root)->right = (*root)->parent = NULL; //setting the  children and the parent of the first node as non_existent(they are considered as black nodes)

	}
	else  //If the set is not empty then we will insert a node which is red
	{
		//Finding the position for the node into the set.If it already exists then we will do nothing

		set_node *y = NULL; //Parent of the node
		set_node *x = *root; //Current node
		
		//We do the same search as in a Binary Search Tree, except in case of equality we return since the elements need to be unique
		while (x != NULL)
		{
			y = x;
			if (cmp(x->value, elem,size) >= 0)
				x = x->left;
			else if (cmp(x->value, elem,size) < 0)
				x = x->right;
		}
		//Creating the node which needs to be inserted
		x = malloc(sizeof(set_node));

		x->color = RED;

		x->left = x->right = NULL;
		x->parent = y;

		x->value = malloc(size);
		memcpy(x->value, elem, size);

		//Inserting the node to the left or the right of the parent,as in a binary search tree.
		if (cmp(y->value, elem) >= 0)
			y->left = x;
		else
			y->right = x;

		
		/*While the parent of the inserted root is red then we are violating the case in which
		  both child and parent should not be red*/

		while (x->parent != NULL && x->parent->color == RED)
		{
			//If the parent is in the left

			if (x->parent->parent->left == x->parent)
			{
				//Store the uncle of the parent
				y = x->parent->parent->right;

				/*Uncle is red so we can make the parent of the uncle red(if is not the root) and 
				  the parent of  the current node and uncle black*/
				if (y != NULL && y->color == RED)
				{
					if (y->parent != NULL)
						y->parent->color = RED;

					y->color = BLACK;
					x->parent->color = BLACK;

					x = x->parent->parent;

				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						left_rotate(root, x);
					}

					x->parent->color = BLACK;
					x->parent->parent->color = RED;

					right_rotate(root, x->parent->parent);
				}

			}
			else if (x->parent->parent->right == x->parent)
			{
				//Store the uncle of the parent
				y = x->parent->parent->left;

				/*Uncle is red so we can make the parent of the uncle red(if is not the root) and
				the parent of  the current node and uncle black*/
				if (y != NULL && y->color == RED)
				{
					if (y->parent != NULL)
						y->parent->color = RED;

					y->color = BLACK;
					x->parent->color = BLACK;

					x = x->parent->parent;

				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						right_rotate(root, x);
					}

					x->parent->color = BLACK;
					x->parent->parent->color = RED;

					left_rotate(root, x->parent->parent);
				}

			}

		}

		(*root)->color = BLACK;


	}
}

void set_delete(set_node *set, void *elem,int size, int(*cmp)(const void*, const void*))
{
	//TODO
}

int set_search(set_node *set, void *elem,int size, int(*cmp)(const void*, const void*))
{
	while (set != NULL)
		if (cmp(set->value, elem) > 0)
			set = set->left;
		else if (cmp(set->value, elem) < 0)
			set = set->right;
		else
			return 1;

   return 0;
}
void sort(set_node *root,void *dest,int size,int *n)
{
	if (root != NULL)
	{
		sort(root->left, dest,size,n);

		memcpy(((char*)dest + (*n)*size), root->value, size);
		*n = *n + 1;
		sort(root->right, dest, size, n);
	}
}