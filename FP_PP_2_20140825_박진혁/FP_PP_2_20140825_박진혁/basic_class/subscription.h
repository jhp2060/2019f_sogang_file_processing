#ifndef __SUBSCRIPTION_H__
#define __SUBSCRIPTION_H__

#include <string>
#include <cstring>
#include <sstream>

#include "Record.h"
#include "../usingIOBuffer.h"

using namespace std;

#define STDMAXBUF 256
#define MAX_SUBSCRIPTION_ID 16 + 1
#define MAX_NEWS_AGENCY_ID 12 + 1
#define MAX_MILEAGE 10 + 1

class Subscription : public Record {
public:
	char subscriptionId[MAX_SUBSCRIPTION_ID];
	char newsAgencyId[MAX_NEWS_AGENCY_ID];
	string memberId;
	char mileage[MAX_MILEAGE];

	Subscription() {}
	Subscription(const char * newId) {
		updateSubscriptionId(newId);
	}
	Subscription(const Subscription& s);

	Subscription &operator = (const Subscription &s);
	bool operator == (const Subscription &s);
	bool operator != (const Subscription &s);

	void updateSubscriptionId(const char *_subscriptionId) {
		memcpy(subscriptionId, _subscriptionId, MAX_SUBSCRIPTION_ID);
	}
	void updateNewsAgencyId(const char *_newsAgencyId) {
		memcpy(newsAgencyId, _newsAgencyId, MAX_NEWS_AGENCY_ID);
	}
	void updateMemberId(const string _memberId) { memberId = _memberId; }
	void updateMileage(const char *_mileage) {
		memcpy(mileage, _mileage, MAX_MILEAGE);
	}

	friend istream & operator >> (istream &is, Subscription &s);
	friend ostream & operator << (ostream &is, Subscription &s);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer &Buffer);

};
istream & operator >> (istream &is, Subscription &s);
ostream & operator << (ostream &is, Subscription &s);

#endif
