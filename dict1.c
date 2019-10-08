/** 
 * dict1.c 
 *
 * This program creates a data structure (BST and Linked List) where it stores
 * information regarding taxi trips and performs searches on said structure 
 * based on key inputs (PUdatetime), returning comparisons based on key input
 * and information based on the search
 *
 * To run the program, the user must give two command line arguments: the first
 * being the data file and the second an output file (where search results are
 * displayed)
**/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"
#include "tree.h"
#include "input.h"

int 
main(int argc, char** argv) {

	FILE* infoDoc; 
	FILE* outputDoc;
	taxiKeys_t* tree = NULL;
	char currentString[MAXCHAR + STRINGBYTE];
	char  stringPUdate[MAXCHAR + STRINGBYTE];
	int comparisons = 0;

	infoDoc = fopen(argv[1], "r");
	outputDoc = fopen(argv[2], "w");
	assert(infoDoc != NULL);
	assert(outputDoc != NULL);

	tree = createDict(tree, currentString, stringPUdate, infoDoc);

	fclose(infoDoc);

	// Performs searches on data structure once input (PUdatetime) is given
	while (scanf(" %[^\n],", currentString) != EOF) {
		searchKey(tree, currentString, outputDoc, &comparisons);
		printf("%s --> %d\n", currentString, comparisons);
		comparisons = 0;
	}

	fclose(outputDoc);
	freeTree(tree);
	free(tree);
	return 0;
}