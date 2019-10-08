/** 
 * tree.h
 * 
 * This header is made for the taxiKeys type - this type is created to make a 
 * BST implementation possible, storing a key (PUdatetime) and a pointer to
 * more data about a particular taxi trip
 *
 * To be compiled with tree.c 
**/

#ifndef TREE_H
#define TREE_H

#define MAXWORDCOUNT 22

typedef struct taxiKeys taxiKeys_t;

struct taxiKeys{
	char* PUdatetime;
	struct taxiInfo* moreData;
	struct taxiKeys* leftNode;
	struct taxiKeys* rightNode;
};

taxiKeys_t* initiateTree(char* key, taxiInfo_t* infoNode);
taxiKeys_t* insertToTree(taxiKeys_t* tree, char* key, taxiInfo_t* infoNode);
void freeTreeNode(taxiKeys_t* treeNode);
void freeTree(taxiKeys_t* tree);
void searchKey(taxiKeys_t* tree, char* keyOfSearch, FILE* outputDoc, 
	           int* comparisons);
void searchLocationID(taxiKeys_t* tree, char* locationID, FILE* outputDoc, 
	                  int* comparisons, int* idFound);
int checkingIDMatch(taxiKeys_t* treeNode, char* locationID, FILE* outputDoc, 
	                int* comparisons);
void putToDoc(taxiKeys_t* treeNode, char* keyOfSearch, FILE* outputDoc);

#endif