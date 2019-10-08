/**
 * input.c
 *
 * This program is responsible for initializing the data structure, as well as
 * storing data into said data structure
 *
 * To be compiled alongside with either dict1.c or dict2.c
**/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"
#include "tree.h"
#include "input.h"

taxiKeys_t*
createDict(taxiKeys_t* tree, char* currentString, char* stringPUdate, 
	       FILE* infoDoc) {

	int curCol;

	// determines if data is still present by checking first column of data
	while (fscanf(infoDoc, " %[^,],", currentString) != EOF) {

		int datalen, stringPUdateCreated = 0;
		taxiInfo_t* infoNode = initiateInfo();

		for (curCol = 0; curCol < (COLUMNS - OFFSET); curCol++) {

			if (curCol == PUDATETIMECOL && !(stringPUdateCreated)) {

				fscanf(infoDoc, "%[^,],", currentString);
				strcpy(stringPUdate, currentString);
				stringPUdateCreated = 1;
				/* value decreased to allow proper indexing of string 
				 * array in taxiInfo struct */
				curCol--;

			} else {

				// to account for lack of comma in scanning for last column 
				if (curCol == LASTCOL) {
					fscanf(infoDoc, "%s", currentString);

				/* to account for the fact that initial column is scanned 
				 * already in while loop */
				} else if (curCol != 0) {
					fscanf(infoDoc, "%[^,],", currentString);
				}

				datalen = strlen(currentString) + STRINGBYTE;
				infoNode->info[curCol] = (char*) malloc(datalen * sizeof(char));
				assert(infoNode->info[curCol] != NULL);
				strcpy(infoNode->info[curCol], currentString);

			}
		}

		tree = insertToTree(tree, stringPUdate, infoNode);
	}

	return tree;
}
