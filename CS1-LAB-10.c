//
// Created by Yimer on 4/18/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct Trie
{
    struct Trie* next[26];
    int count;
}Trie;

// Inserts the word to the trie structure
void insert(Trie *pTrie, char *word)
{
    int counter = 0, val;
    Trie* temp = pTrie;
    while (word[counter] != '\0') {
        val = word[counter] - 'a';
        if (temp->next[val] == NULL) {
            temp->next[val] = (Trie*) calloc(1, sizeof(Trie));
        }
        temp = temp->next[val];
        counter++;
    }
    temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(Trie *pTrie, char *word)
{
    int counter = 0, val, NumOfOcurrances = 0;
    Trie* temp = pTrie;
    while (word[counter] != '\0') {
        val = word[counter] - 'a';
        if (temp->next[val] == NULL) {
            return 0;
        }
        temp = temp->next[val];
        counter++;
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(Trie *pTrie)
{
    int count = 0;
    for (count= 0; count < 26; count++) {
        if (pTrie->next[count] != NULL) {
            pTrie->next[count] = deallocateTrie(pTrie->next[count]);
        }
    }
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    Trie* newRoot = (Trie*) calloc(1, sizeof(Trie));
    return newRoot;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* f = fopen(filename, "r");
    int counter, end;
    fscanf(f, "%d\n", &end);
    for (counter = 0; counter<end; counter++) {
        pInWords[counter] = (char*) malloc(sizeof(char)*50);
        fscanf(f, "%s", pInWords[counter]);
    }
}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}