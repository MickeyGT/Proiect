#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/*
	Different type explanations:
	1 -> Straight up insert, requires name, definiton and will also add 1 to first line to specify 1 definition.
	2 -> Splits into 4 cases: 1. Update a single definition.(Will be given as a parameter in the test cases)
							  2. Clear the word definitions.
							  3. Add a new definition for the respective word.
							  4. Remove a single definiton.(Will be given as a parameter in the test cases)
	3 -> Look-up a word and show its definitions.

	How the file layout for each word will be:
	First line will represent the number of definitions our word has.(defnum)
	The next defnum lines will consist of strings where each one represents a definition for that word.
*/

// A function which generates a random number in the interval [a,b]
int random_numb(int a, int b)
{
	return a + rand() % (b - a + 1);
}

// Vector which holds all the possible words from a dictionary
char words[110000][30];

// Number of definitions for a random word
int size_def[110000];

//Word is inserted

int word_is[110000];

// Total number of words which can be random selected
int word_size;

// All possible letters that should be random generated 
char letters[53] = "qwertyiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";

// Input file
FILE *in,*out;

int main()
{
	int N , i, j;

	scanf("%d", &N); // Reading the number of total operations

	in = fopen("words.in", "r");
	out = fopen("test6.out", "w");

	fprintf(out, "%d\n", N);

	//Reading all the words from the dictionary
	while (!feof(in))
	{
		fgets(words[word_size], 40, in);
		word_size++;
	}

	srand(time(NULL));

	for (i = 1;i <= N;++i)
	{
		int command, sub_command, spec_word, spec_def;

		command = random_numb(1, 3); // Random command
		spec_word = random_numb(0, word_size - 1); //A random index of a word from the dictionary
		spec_def = random_numb(1, 80); // A random size for the definition

		if (command == 1)
		{
			if (word_is[spec_word] == 0)
			{
				word_is[spec_word] = 1;

				//Printing the command
				fprintf(out, "%d ", command);

				//Priting the word
				for (j = 0;words[spec_word][j] != '\n';++j)
					fprintf(out, "%c", words[spec_word][j]);

				fprintf(out, " ");

				//Priting a definiton with random letters
				for (j = 1;j <= spec_def;++j)
					fprintf(out, "%c", letters[random_numb(0, 51)]);

				fprintf(out, "\n");

				//Making the size of specific word 1, since it has just a definition
				size_def[spec_word] = 1;
			}
			else
				--i;
		}
		else if (command == 2)
		{
			
			sub_command = random_numb(1, 4);

			if (sub_command == 1)
			{
				//No modification to the array of definitons for a word since it is an update and the size will not be altered
				if (size_def[spec_word] >= 1)
				{
					fprintf(out, "%d %d %d ", command, sub_command, random_numb(1, size_def[spec_word])); // Generate a random index for the definition which must be updated

					for (j = 0;words[spec_word][j] != '\n';++j)
						fprintf(out, "%c", words[spec_word][j]);

					fprintf(out, " ");

					for (j = 1;j <= spec_def;++j)
						fprintf(out, "%c", letters[random_numb(0, 51)]);

					fprintf(out, "\n");
				}
				else
					--i; // If the size of definition is not greater or equal than 1 it means that the following subcommand must pe skipped
			}
			else if (sub_command == 2)
			{
				fprintf(out,"%d %d ", command, sub_command);

				for (j = 0;words[spec_word][j] != '\n';++j)
					fprintf(out, "%c", words[spec_word][j]);

				fprintf(out, "\n");


				//Clearing the number of definition for a word
				size_def[spec_word] = 0;
			}
			else if (sub_command== 3)
			{
				fprintf(out, "%d %d ", command, sub_command);

				for (j = 0;words[spec_word][j] != '\n';++j)
					fprintf(out, "%c", words[spec_word][j]);

				fprintf(out, " ");

				for (j = 1;j <= spec_def;++j)
					fprintf(out, "%c", letters[random_numb(0, 51)]);
				fprintf(out, "\n");

				//Increasing the number of definitions for a word
				size_def[spec_word]++;
			}
			else
			{
				if (size_def[spec_word] - 1 >= 0)
				{
					fprintf(out, "%d %d %d ", command, sub_command, random_numb(1, size_def[spec_word])); // Generating a random index for the definition which must be deleted

					for (j = 0;words[spec_word][j] != '\n';++j)
						fprintf(out, "%c", words[spec_word][j]);

					fprintf(out, "\n");

					//Decrementing the number of definition for the word
					size_def[spec_word]--;
				}
				else
					--i; //If it is no definition to delete then we skip the step
			}
		}
		else if (command == 3)
		{

			fprintf(out, "%d ", command);
			for (j = 0;words[spec_word][j] != '\n';++j)
				fprintf(out, "%c", words[spec_word][j]);

			fprintf(out, "\n");
		}

	}

	return 0;
}
