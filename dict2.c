/** 
 * dict2.c 
 *
 * This program creates a data structure (BST and Linked List) where it stores
 * information regarding taxi trips and performs searches on said structure 
 * based on key inputs (PUlocationID), returning comparisons based on key input
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
	char stringPUdate[MAXCHAR + STRINGBYTE];

	// idFound variable serves to identify if search is successful 
	int comparisons = 0, idFound = 0;

	infoDoc = fopen(argv[1], "r");
	outputDoc = fopen(argv[2], "w");
	assert(infoDoc != NULL);
	assert(outputDoc != NULL);

	tree = createDict(tree, currentString, stringPUdate, infoDoc);

	fclose(infoDoc);

	while (scanf(" %[^\n],", currentString) != EOF) {
		searchLocationID(tree, currentString, outputDoc, &comparisons, 
						 &idFound);
		if (idFound == NONE) {
			fprintf(outputDoc, "%s --> %s\n", currentString, NOTFOUND);
		}
		printf("%s --> %d\n", currentString, comparisons);
		idFound = 0; comparisons = 0;
	}

	fclose(outputDoc);
	freeTree(tree);
	free(tree);
	return 0;
}