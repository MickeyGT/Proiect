/**
*@mainpage
* \brief \b Problem \b Application 6: A dictionary application
* \author Turcu Gabriel and Stoica Alexandru
* \date 30.05.2016
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "set.h"
#include"dictionary.h"

/** The variable n will be used to store the number of commands our algorithm will go through. */
int n;
/** The variable type will be used to store the current operation we will have to perform. */
int type;
/** Prameter used in different for's throughout the program.*/
int k
/** The vector word is used to store the word we're currently working with. */;
char word[100];
/** The vector definition is used to store the current definition we're working with.*/
char definition[100];
/** The char matrix eword is used to store the entire content of the word we're currently updating.*/
char eword[1000][100];

set_node *set;
///> This is the file that contains the commands for the program.
FILE *fi;
/** Reading function used to initialize and see if our file exists and if it does, it reads n. @see n*/
int Reading()
{
	fi = fopen("test10.out", "r");
	if (fi == NULL)
		return 0;
	set_init(&set);
	fscanf(fi, "%d", &n);
	return 1;
}
void Compute()
{
	fscanf(fi, "%d", &type);
	if (type == 1)                 /// Type 1 is for Inserting a word into the dictionary.
		InsertSequence(fi, &set, word, definition);
	else
		if (type == 2)                 /// Type 2 is for updating a word and it's definitions.
			UpdateSequence(fi, &set, word, definition, eword);
		else
			if (type == 3)                /// Type 3 for looking up a word's definitions and displaying them in the console.
				SearchSequence(fi, &set, word, definition, eword);
}
int main()
{
	/*
	*Different type explanations:
	*1 -> Straight up insert, requires name, definiton and will also add 1 to first line to specify 1 definition.
	*2 -> Splits into 4 cases: 1. Update a single definition.(Will be given as a parameter in the test cases)
	*						  2. Clear the word definitions.
	*                         3. Add a new definition for the respective word.
	*                         4. Remove a single definiton.(Will be given as a parameter in the test cases)
	*3 -> Look-up a word and show its definitions.
	*
	*How the file layout for each word will be:
	*First line will represent the number of definitions our word has.(defnum)
	*The next defnum lines will consist of strings where each one represents a definition for that word.
	*/
	if (!Reading())
	{
		printf("The file couldn't be opened.");
		return 0;
	}
	for (k = 1;k <= n;k++)
		Compute();
	system("pause");
	return 0;
}