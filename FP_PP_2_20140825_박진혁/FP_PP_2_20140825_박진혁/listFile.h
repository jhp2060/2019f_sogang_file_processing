#ifndef __LIST_FILE_H__
#define __LIST_FILE_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "basic_class/member.h"
#include "basic_class/newsAgency.h"
#include "basic_class/subscription.h"
#include "iobuffer/recfile.h"

#define MIN_MEMBER_REC 1000
#define MIN_NEWS_AGECNY_REC 1000
#define MIN_SUBSCRIPTION_REC 10000
#define MIN(x,y) (((x)>(y))?(y):(x))


using namespace std;

void generateMemberList(int size);
void generateNewsAgencyList(int size);
void generateSusbscriptionList(int size,
	int newsAgencySize, int memberSize);

string generateRandomNumber(int digit);
string intToString(int integer, int digit);


// when using template, we should define and implement a funciton in the same file

// get the file name for generating .txt file according to the data type
template <class T>
char* getListFileName() {
	if (is_same<T, Member>::value)
		return "listOfMember.txt";
	else if (is_same<T, NewsAgency>::value)
		return "listOfNewsAgency.txt";
	else if (is_same<T, Subscription>::value)
		return "listOfSubscription.txt";
}


// get the .dat file name for each data type
template <class T>
char* getDataFileName() {
	if (is_same<T, Member>::value)
		return "fileOfMember.dat";
	else if (is_same<T, NewsAgency>::value)
		return "fileOfNewsAgency.dat";
	else if (is_same<T, Subscription>::value)
		return "fileOfSubscription.dat";
}


// project2
template <class T>
char* getFileNameNoExtension() {
	if (is_same<T, Member>::value)
		return "fileOfMember";
	else if (is_same<T, NewsAgency>::value)
		return "fileOfNewsAgency";
	else if (is_same<T, Subscription>::value)
		return "fileOfSubscription";
}

template <class T>
char* getIndexFileName() {
	if (is_same<T, Member>::value)
		return "fileOfMember.ind";
	else if (is_same<T, NewsAgency>::value)
		return "fileOfNewsAgency.ind";
	else if (is_same<T, Subscription>::value)
		return "fileOfSubscription.ind";
}

template <class T>
int getMaxRecordNumber() {
	return 10000;
	/*if (is_same<T, Member>::value)
		return 1000;
	else if (is_same<T, NewsAgency>::value)
		return 1000;
	else if (is_same<T, Subscription>::value)
		return 10000;*/
}

template <class T>
int getMaxRecordKeyLength() {
	if (is_same<T, Member>::value)
		return 30;
	else if (is_same<T, NewsAgency>::value)
		return 12;
	else if (is_same<T, Subscription>::value)
		return 16;
}
#endif
