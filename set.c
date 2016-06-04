#include"set.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void set_init(set_node **set)
{
	/*!
	* 	\param set A pointer to the red-black tree structure.
	*/

	*set = NULL;
}

/// Performs a left rotation in the red-black tree.
void left_rotate(set_node **root, set_node *node)
{
	/*!
	* 	\param root A pointer to the root red-black tree structure.
	*   \param node A pointer to the node from where the rotation should begin
	*/

	///Set z as the right child.
	set_node *z = node->right;

	///Right child of node becomes the left child of the right child of the node.
	node->right = z->left;

	///If the right child,now moved is not null it means that is has a parent and we must update it.
	if (z->left != NULL)
		z->left->parent = node;

	///Update the parent of the initial right child of the node.
	z->parent = node->parent;

	///Update the child of the parent of the initial node.
	if (node->parent == NULL)
		(*root) = z;
	else if (node->parent->left == node)
		node->parent->left = z;
	else
		node->parent->right = z;

	///Update the child of the the right child of the initial node.
	z->left = node;

	///Update the parent of the initial node
	node->parent = z;

}

/// Performs a right rotation in the red-black tree. 
 void right_rotate(set_node **root, set_node *node)
{
	/*!
	* 	\param root A pointer to the root red-black tree structure.
	*	\param node A pointer to the node from where the rotation should begin
	*/

	///Set z as the left child
	set_node *z = node->left;


	///Left child of node becomes the right child of the left child of the node
	node->left = z->right;

	///If the left child,now moved is not null it means that is has a parent and we must update it
	if (z->right != NULL)
		z->right->parent = node;

	///Update the parent of the initial left child of the node
	z->parent = node->parent;

	///Update the child of the parent of the initial node
	if (node->parent == NULL)
		(*root) = z;
	else if (node->parent->right == node)
		node->parent->right = z;
	else
		node->parent->left = z;

	///Update the child of the the left child of the initial node
	z->right = node;

	///Update the parent of the initial node
	node->parent = z;

}

void set_insert(set_node **root, void *elem, const int size, int(*cmp)(const void*, const void*))
{

	/*!
	* 	\param root A pointer to the red-black tree's root.
	* 	\param elem Element which should be inserted.
	* 	\param size The side of the element which should be inserted.
	* 	\param cmp A comparator which should return the following values for these cases: -1 - compares less, 0 - equal , 1- doesn't compare less.
	*/

	/// If the set is empty then it will insert a node which is black, storing the elem inside it and making the childs and partent NULL.

	if (*root == NULL)
	{
		(*root) = malloc(sizeof(set_node)); ///Allocating size for the set

		(*root)->color = BLACK; ///Setting the color black of the first node
		(*root)->value = malloc(size); ///Allocating size for the value which needs to be stored

		memcpy((*root)->value, elem, size); ///Copying the element into the node

		(*root)->left = (*root)->right = (*root)->parent = NULL; ///Setting the  children and the parent of the first node as non_existent(they are considered as black nodes)

	}
	///If set is not empty then it will insert a node which is red
	else
	{
		/// It find the position for the node into the set.If it already exists then it will do nothing

		///Parent of the node
		set_node *y = NULL; 
		///Current node
		set_node *x = *root; 

							 /// The search is the same as in a Binary Search Tree, except the case of equality in which the function will terminate
		while (x != NULL)
		{
			y = x;
			if (cmp(x->value, elem) > 0)
				x = x->left;
			else if (cmp(x->value, elem) < 0)
				x = x->right;
			else
				return;
		}
		///Creating the node which needs to be inserted
		x = malloc(sizeof(set_node));

		x->color = RED;

		x->left = x->right = NULL;
		x->parent = y;

		x->value = malloc(size);
		memcpy(x->value, elem, size);

		///Inserting the node to the left or the right of the parent,as in a binary search tree.
		if (cmp(y->value, elem) > 0)
			y->left = x;
		else
			y->right = x;


		/// While the proprieties of red-black tree are broken after the insertion of the desired node  3 cases will be covered:
		/// The case in which no rotation is needed, just a change a of coloring
		/// The case in which a single rotation is needed
		/// The case in which 2 rotation are needed 
		while (x->parent != NULL && x->parent->color == RED)
		{
			///If the parent is in the left

			if (x->parent->parent->left == x->parent)
			{
				///Store the uncle of the parent
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

int set_search(set_node *set, void *elem, int(*cmp)(const void*, const void*))
{
	/*!
	* 	\param set A pointer to the set.
	* 	\param elem Element which should be searched
	* 	\param cmp A comparator which should return the following values for these cases: -1 - compares less, 0 - equal , 1- doesn't compare less.
	*/

	while (set != NULL)
		if (cmp(set->value, elem) > 0)
			set = set->left;
		else if (cmp(set->value, elem) < 0)
			set = set->right;
		else
			return 1;

		return 0;
}