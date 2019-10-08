/**
 * info.h
 * 
 * This header is made for the taxiInfo type - this type is created to store 
 * miscellaneous and non-pertinent information of one or multiple taxi trips
 * if PUdatetime for these trips are similar
 *
 * To be compiled alongside with info.c
**/

#ifndef INFO_H
#define INFO_H

typedef struct taxiInfo taxiInfo_t;

struct taxiInfo{
	char** info;
	struct taxiInfo* nextNode;
};

taxiInfo_t* initiateInfo();
taxiInfo_t* returnLastNode(taxiInfo_t* infoNode);
void freeInfo(taxiInfo_t* infoNode);

#endif 