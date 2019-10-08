/**
 * info.c
 * 
 * This program describes the many functions that can be performed on the 
 * taxiInfo type (struct), including its creation and deletion in dynamic
 * memory
 *
 * Compiled along with dict1.c or dict2.c
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "info.h"
#include "tree.h"
#include "input.h"

taxiInfo_t*	
initiateInfo() {

	taxiInfo_t* infoNode;

	infoNode = (taxiInfo_t*) malloc(sizeof(taxiInfo_t));
	assert(infoNode != NULL);

	infoNode->info = (char**) malloc((COLUMNS - OFFSET) * sizeof(char*));
	assert(infoNode->info != NULL);

	infoNode->nextNode = NULL;
	return infoNode;
}

taxiInfo_t* 
returnLastNode(taxiInfo_t* infoNode) {

	taxiInfo_t* tmp = infoNode;

	while (tmp->nextNode != NULL) {
		tmp = tmp->nextNode;
	}

	return tmp;
}

void
freeInfo(taxiInfo_t* infoNode) {

	int col;
	taxiInfo_t* prevNode;
	
	while (infoNode != NULL) {
		for (col = 0; col < (COLUMNS - OFFSET); col++) {
			free(infoNode->info[col]);
		}
		free(infoNode->info);
		prevNode = infoNode;
		infoNode = infoNode->nextNode;
		free(prevNode);
	}
}
