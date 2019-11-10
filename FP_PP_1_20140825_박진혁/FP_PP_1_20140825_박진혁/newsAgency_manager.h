#ifndef __NEWSAGENCY_MANAGER_H__
#define __NEWSAGENCY_MANAGER_H__

#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include "usingIOBuffer.h"
#include "./basic_class/subscription.h"
#include "./basic_class/newsAgency.h"
#include "subscription_manager.h"
#include "listFile.h"

#define MIN_NEWS_AGENCY_DUMMY_RECORD_LEN (2 + 3 + 12)

using namespace std;

class NewsAgencyManager {
public:
	bool newsAgencySearch(string newsAgencyId);
	void newsAgencyInsert();
	void newsAgencyUpdate();
	void newsAgencyDelete(string newsAgencyId);
};

int getNewsAgencyRecordLen(NewsAgency n);
void makeDummyNewsAgency(NewsAgency &n, int deletedRecordLen);
void saveNewsAgencyRecord(NewsAgency newNewsAgency);

#endif