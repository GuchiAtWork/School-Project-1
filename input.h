/**
 * input.h
 *
 * This header represents the input function, as well as all constants needed 
 * across multiple programs
 *
 * To be compiled alongside with input.c
**/

#ifndef INPUT_H
#define INPUT_H

#define MAXCHAR 128
#define COLUMNS 18
#define PUDATETIMECOL 15
#define LASTCOL 16	
#define STRINGBYTE 1
#define OFFSET 1
#define NOTFOUND "NOTFOUND"
#define PULOCATIONID 5
#define NONE 0

taxiKeys_t* createDict(taxiKeys_t* tree, char* currentString, 
	                   char* stringPUdate, FILE* infoDoc);

#endif  