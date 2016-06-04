#include<stdio.h>
#include"dictionary.h"
#include<string.h>
#include<stdlib.h>

void InsertSequence(FILE *fi, set_node **set, char *word, char *definition)
{
	/*!
	* 	\param fi Input file.
	* 	\param set The set in which the elements will be inserted.
	* 	\param word The vector word is used to store the word we're currently inserting.
	* 	\param definition The vector definition is used to store the current definition we're going to insert.
	*/

	fscanf(fi, "%s", word);
	fgetc(fi);
	fgets(definition, 100, fi);
	///> We check if the word already exists and if it does not, we proceed with the InsertSequence().
	if (!(set_search(*set, word, (int(*)(const void *, const void *)) strcmp)))
	{
		///> We use set_insert() to insert the word in the set.
		set_insert(set, word, strlen(word) + 1, (int(*)(const void *, const void *))strcmp);
		FILE *f = fopen(word, "w");
		fprintf(f, "1\n");                 // We will use the first line of the file to store the number of definitions our word has. In the insert case, we initialize it with 1.
		fprintf(f, "%s\n", definition);                 // The definition as the second line in the file.
		fclose(f);
	}
}

void UpdateSequence(FILE *fi, set_node **set, char *word, char *definition, char eword[1000][100])
{
	/*!
	* 	\param fi Input file.
	* 	\param set The set in which the elements will be inserted.
	* 	\param word The vector word is used to store the word we're currently inserting.
	* 	\param definition The vector definition is used to store the current definition we're going to insert.
	*   \param eword The char matrix eword is used to store the entire content of the word we're currently updating.
	*/

	int sectype, defnumber, defnum, i, j;

	/// \param sectype The secondary type of our 4 cases mentioned above at main type 2
	fscanf(fi, "%d", &sectype);
	fgetc(fi);
	/// \param defnumber The number that represents the definition we'll update or remove.
	if ((sectype == 1) || (sectype == 4))                 /// For secondary type 1 and 4 we will also require the definition number we will update or delete. 
		fscanf(fi, "%d", &defnumber);
	fscanf(fi, "%s", word);
	fgetc(fi);
	if (sectype != 4 && sectype != 2)                 /// If secondary type is 2 or 4 we will not require a definition and therefore not read one.
		fgets(definition, 100, fi);
	/// ---------------------------------------------------------------------
	if (sectype == 1)               /// Secondary type 1 for updating a specific definition.
	{
		if (set_search(*set, word, (int(*)(const void *, const void *))strcmp))
		{
			FILE *f = fopen(word, "r");
			fscanf(f, "%d", &defnum);                 /// We read the number of definitions our word currently has.
			fgetc(f);
			for (i = 0;i <= defnum - 1;i++)
				fgets(eword[i], 100, f);                 /// We put all our definitions in a char matrix, one for each line.
			strcpy(eword[defnumber - 1], definition);                 /// We update the definition by writing over it in the matrix our new definition.
			fclose(f);
			FILE *g = fopen(word, "w");                 // 
			fprintf(g, "%d\n", defnum);                 // 
			for (i = 0;i <= defnum - 1;i++)             // 
			{                                           //  Sequence for writing our modified matrix back in the file. 
				for (j = 0;eword[i][j] != '\0';j++)     // 
					fprintf(g, "%c", eword[i][j]);      //
														// 
			}
			fprintf(g, "\n");
			fclose(g);
		}
	}
	/// ---------------------------------------------------------------------
	if (sectype == 2)                 /// Secondary type 2 for clearing a word of its definitions.
	{
		if (set_search(*set, word, (int(*)(const void *, const void *)) strcmp))
		{
			FILE *f = fopen(word, "w");
			fprintf(f, "0\n");                 /// In order to clear a word of its definitions, we just reset the number of definitions on the first line with 0.
			fclose(f);
		}
	}
	/// ---------------------------------------------------------------------
	if (sectype == 3)                 /// Secondary type 3 for adding a new definition in the end to an already existing word.
	{
		if (set_search(*set, word, (int(*)(const void *, const void *))strcmp))
		{
			FILE *f = fopen(word, "r");
			fscanf(f, "%d", &defnum);
			fgetc(f);
			for (i = 0;i <= defnum - 1;i++)
				fgets(eword[i], 100, f);
			defnum++;                 /// We increase the defnumber since we've added a new one in this case.
			strcpy(eword[defnum - 1], definition);                 /// We add the new definition on the last line of the matrix.
			fclose(f);
			FILE *g = fopen(word, "w");
			fprintf(g, "%d\n", defnum);
			for (i = 0;i <= defnum - 1;i++)						    // 
			{														//
				for (j = 0;eword[i][j] != '\0';j++)                 //   Sequence for writing our modified matrix back in the file.    
					fprintf(g, "%c", eword[i][j]);                  //
			}													    //
			fprintf(g, "\n");									    //
			fclose(g);
		}
	}
	/// ---------------------------------------------------------------------
	if (sectype == 4)                 /// Secondary type 4 for removing a definition of an already existing word.
	{
		if (set_search(*set, word, (int(*)(const void *, const void *))strcmp))
		{
			FILE *f = fopen(word, "r");
			fscanf(f, "%d", &defnum);
			fgetc(f);
			for (i = 0;i <= defnum - 1;i++)                 /// We read the matrix of definitions from the file.
				fgets(eword[i], 100, f);
			for (i = defnumber;i <= defnum - 1;i++)
				strcpy(eword[i - 1], eword[i]);                 /// For each definition after the one we want to delete, we just move them one row back, deleting the definition we wanted to remove.
			defnum--;                 /// We decrease the number of definitions since we just deleted one.
			fclose(f);
			FILE *g = fopen(word, "w");
			fprintf(g, "%d\n", defnum);
			for (i = 0;i <= defnum - 1;i++)                         //
			{														//
				for (j = 0;eword[i][j] != '\0';j++)                 //    Sequence for writing our modified matrix back in the file.  
					fprintf(g, "%c", eword[i][j]);                  //
			}														//
			fprintf(g, "\n");                                       //
			fclose(g);
		}
	}
}
void SearchSequence(FILE *fi, set_node **set, char *word, char *definition, char eword[1000][100])
{
	/*!
	* 	\param fi Input file.
	* 	\param set The set in which the elements will be inserted.
	* 	\param word The vector word is used to store the word we're currently inserting.
	* 	\param definition The vector definition is used to store the current definition we're going to insert.
	*   \param eword The char matrix eword is used to store the entire content of the word we're currently updating.
	*/

	int defnum, i, j;

	fscanf(fi, "%s", word);
	fgetc(fi);
	if (set_search(*set, word, (int(*)(const void *, const void *))strcmp))
	{
		FILE *f = fopen(word, "r");
		fscanf(f, "%d", &defnum);
		fgetc(f);
		for (i = 0;i <= defnum - 1;i++)                 /// Creating the matrix with the definitions for our word.
			fgets(eword[i], 100, f);
		printf("The definitions for the word %s are:\n", word);
		for (i = 0;i <= defnum - 1;i++)                 /// For this case we just print the content of the matrix for the respective word.
		{
			for (j = 0;eword[i][j] != '\0';j++)
				printf("%c", eword[i][j]);
		}
		printf("\n");
		fclose(f);
	}
}