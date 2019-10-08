/**
 * tree.c
 *
 * This program represents the functions needed to initialize, update and search
 * contents in a modified binary search tree pertinent to the project
 *
 * To be compiled along with either dict1.c or dict2.c
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "info.h"
#include "tree.h"
#include "input.h"

taxiKeys_t*
initiateTree(char* key, taxiInfo_t* infoNode) {

	int keylen = strlen(key) + STRINGBYTE;
	taxiKeys_t* tree;

	tree = (taxiKeys_t*) malloc(sizeof(taxiKeys_t));
	assert(tree != NULL);

	tree->PUdatetime = (char*) malloc(keylen * sizeof(char));
	assert(tree->PUdatetime != NULL);

	strcpy(tree->PUdatetime, key);
	tree->moreData = infoNode;
	tree->leftNode = NULL;
	tree->rightNode = NULL;
	return tree;
}

taxiKeys_t*
insertToTree(taxiKeys_t* tree, char* key, taxiInfo_t* infoNode) {

	taxiKeys_t* tmptree = tree;
	taxiInfo_t* lastNode;

	if (tree == NULL) {
		return initiateTree(key, infoNode);
	}

	while (tmptree != NULL) {

		if (strcmp(tmptree->PUdatetime, key) < 0) {
			if (tmptree->rightNode == NULL) {
				tmptree->rightNode = initiateTree(key, infoNode);
				break;
			}
			tmptree = tmptree->rightNode;

		} else if (strcmp(tmptree->PUdatetime, key) > 0) {
			if (tmptree->leftNode == NULL) {
				tmptree->leftNode = initiateTree(key, infoNode);
				break;
			}
			tmptree = tmptree->leftNode;

		/* in the case that current data's PUdatetime is equal to one of the 
		 * keys in the data structure */
		} else {
			lastNode = returnLastNode(tmptree->moreData);
			lastNode->nextNode = infoNode;
			return tree;
		}

	}

	return tree;
}

void
freeTreeNode(taxiKeys_t* treeNode) {

	free(treeNode->PUdatetime);
	freeInfo(treeNode->moreData);
	free(treeNode->leftNode);
	free(treeNode->rightNode);
}

/* This function utilizes a post order traversal to free all nodes within the
 * tree */
void 
freeTree(taxiKeys_t* tree) {

	if (tree == NULL) {
		return;
	}
	freeTree(tree->leftNode);
	freeTree(tree->rightNode);
	freeTreeNode(tree);
}

void
searchKey(taxiKeys_t* tree, char* keyOfSearch, FILE* outputDoc, 
	      int* comparisons) {

	taxiKeys_t* tmp = tree;

	// finds which node has the key of search (or if it exists at all)
	while (tmp != NULL) {

		if (strcmp(tmp->PUdatetime, keyOfSearch) < 0) {
			*comparisons += 1;
			tmp = tmp->rightNode;

		} else if (strcmp(tmp->PUdatetime, keyOfSearch) > 0) {
    		*comparisons += 1;
			tmp = tmp->leftNode;

		} else {
			*comparisons += 1;
			break;
		}
	}

	putToDoc(tmp, keyOfSearch, outputDoc);
}

/* Function inputs certain contents into file depending on the node of the tree
 * given (or if it exists at all) */
void
putToDoc(taxiKeys_t* treeNode, char* keyOfSearch, FILE* outputDoc) {

	char headers[][MAXWORDCOUNT] = {"VendorID", "passenger_count", 
									"trip_distance", "RatecodeID", 
									"store_and_fwd_flag", "PULocationID", 
									"DOLocationID", "payment_type", 
									"fare_amount", "extra", "mta_tax", 
									"tip_amount", "tolls_amount", 
									"improvement_surcharge", "total_amount", 
									"DOdatetime", "trip_duration"};

	if (treeNode == NULL) {
		fprintf(outputDoc, "%s --> %s\n", keyOfSearch, NOTFOUND);
	} else {

		int col;
		taxiInfo_t* curNode = treeNode->moreData;

		// responsible for printing out content in linked list 
		while (curNode != NULL) {

			fprintf(outputDoc, "%s --> ", keyOfSearch);

			for (col = 0; col < (COLUMNS - OFFSET); col++) {
				if (col == (COLUMNS - OFFSET - 1)) {
					fprintf(outputDoc, "%s: %s ||", headers[col], 
						    curNode->info[col]);
				} else {
					fprintf(outputDoc, "%s: %s || ", headers[col], 
						    curNode->info[col]);
				}
			}

			fprintf(outputDoc, "\n");
			curNode = curNode->nextNode;
		}
	}
}

/* Function utilises in-order traversal to sequentially determine taxi trips in
 * a specific PUlocationID */
void 
searchLocationID(taxiKeys_t* tree, char* locationID, FILE* outputDoc, 
	             int* comparisons, int* idFound) {

	if (tree == NULL) {
		return;
	}
	searchLocationID(tree->leftNode, locationID, outputDoc, comparisons, 
		             idFound);

	// variable represents how many times PUlocationID has been spotted
	*idFound += checkingIDMatch(tree, locationID, outputDoc, comparisons);

	searchLocationID(tree->rightNode, locationID, outputDoc, comparisons, 
		             idFound);	
}

int
checkingIDMatch(taxiKeys_t* treeNode, char* locationID, FILE* outputDoc, 
	            int* comparisons) {

	taxiInfo_t* tmpNode = treeNode->moreData;
	int matchAmounts = 0;

	/* goes through linked list in each tree node to determine if specifc
	 * location is found */
	while (tmpNode != NULL) {
		if (strcmp(tmpNode->info[PULOCATIONID], locationID) == 0) {
			matchAmounts++;
			fprintf(outputDoc, "%s --> %s\n", locationID, treeNode->PUdatetime);	
		}
		*comparisons += 1;
		tmpNode = tmpNode->nextNode;
	}

	return matchAmounts;
}