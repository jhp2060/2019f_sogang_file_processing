#ifndef __SUBSCRIPTION_MANAGER_H__
#define __SUBSCRIPTION_MANAGER_H__

#include <string>
#include <cstring>
#include <sstream>
#include <vector>

#include "usingIOBuffer.h"
#include "./basic_class/newsAgency.h"
#include "./basic_class/subscription.h"
#include "listFile.h"
#include "member_manager.h"
#include "newsAgency_manager.h"

#define MIN_SUBSCRIPTION_DUMMY_RECORD_LEN (2 + 4)

class SubscriptionManager {
public:
	Subscription* subscriptionSearch(string subscriptionId);
	void subscriptionInsert();
	void subscriptionUpdate();
	void subscriptionDelete(string subscriptionId);

	// project2
	void mySubscriptionInsert(string memberId);
	void mySubscriptionUpdate(string memberId);

};

void subscriptionDeleteWithMemberId(string memberId);
void subscriptionDeleteWithNewsAgencyId(string newsAgencyId);

int getSubscriptionRecordLen(Subscription s);
void makeDummySubscription(Subscription &s, int deletedRecordLen);
void saveSubscriptionRecord(Subscription newSubscription);

#endif
