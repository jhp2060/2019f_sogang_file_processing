#ifndef __REGISTER_MANAGER_H__
#define __REGISTER_MANAGER_H__

#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include "usingIOBuffer.h"
#include "./basic_class/newsAgency.h"
#include "./basic_class/subscription.h"
#include "listFile.h"

#define MIN_SUBSCRIPTION_DUMMY_RECORD_LEN (2 + 4 + (16 + 12 + 10))

class SubscriptionManager {
public:
	bool subscriptionSearch(string subscriptionId);
	void subscriptionInsert();
	void subscriptionUpdate();
	void subscriptionDelete(string subscriptionId);
};

void subscriptionDeleteWithMemberId(string memberId);
void subscriptionDeleteWithNewsAgencyId(string newsAgencyId);

int getSubscriptionRecordLen(Subscription s);
void makeDummySubscription(Subscription &s, int deletedRecordLen);
void saveSubscriptionRecord(Subscription newSubscription);

#endif
