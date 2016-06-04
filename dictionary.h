#ifndef DICTIONARY_H
#define DICTIONARY_H
#include<stdio.h>
#include"set.h"

/// This function deals with Inserting a new word to the dictionary. 
void InsertSequence(FILE *fi, set_node **set, char *word, char *definition);
/// This function deals with Updating a word from the dictionary. 
void UpdateSequence(FILE *fi, set_node **set, char *word, char *definition, char eword[1000][100]);
/// This function deals with Searcing a word in the dictionary.
void SearchSequence(FILE *fi, set_node **set, char *word, char *definition, char eword[1000][100]);



#endif