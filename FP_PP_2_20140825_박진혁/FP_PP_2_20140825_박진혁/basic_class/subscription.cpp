#include "subscription.h"

Subscription::Subscription(const Subscription &s) {
    updateSubscriptionId(s.subscriptionId);
    updateNewsAgencyId(s.newsAgencyId);
    updateMemberId(s.memberId);
    updateMileage(s.mileage);
}

Subscription &Subscription::operator = (const Subscription &s){
	updateSubscriptionId(s.subscriptionId);
	updateNewsAgencyId(s.newsAgencyId);
	updateMemberId(s.memberId);
	updateMileage(s.mileage);

    return *this;
}

bool Subscription::operator == (const Subscription &s) {
	return !memcmp(subscriptionId, s.subscriptionId, MAX_SUBSCRIPTION_ID);
}

bool Subscription::operator != (const Subscription &s) {
    return memcmp(subscriptionId, s.subscriptionId, MAX_SUBSCRIPTION_ID);
}

istream & operator >> (istream &is, Subscription &s) {
    string str;
    is.exceptions(istream::failbit | istream::badbit);

    try {
        getline(is,str);
    } catch (istream::failure e) {
        return is;
    }

    istringstream iss(str);
    string token;

    getline(iss, token, '|');
    s.updateSubscriptionId(token.data());
    getline(iss, token, '|');
    s.updateNewsAgencyId(token.data());
    getline(iss, token, '|');
    s.updateMemberId(token);
    getline(iss, token, '|');
    s.updateMileage(token.data());

    return is;
}

ostream & operator << (ostream &os, Subscription &s) {
    string mSubscriptionId(s.subscriptionId, MAX_SUBSCRIPTION_ID);
    string mNewsAgencyId(s.newsAgencyId, MAX_NEWS_AGENCY_ID);
    string mMileage(s.mileage, MAX_MILEAGE);

    os << "SUBSCRIPTION ID : " << mSubscriptionId << endl;
    os << "NEWSAGENCY ID : " << mNewsAgencyId << endl;
    os << "MEMBER ID : " << s.memberId << endl;
    os << "MILEAGE : " << mMileage << endl;

    return os; 
}
bool Subscription::Pack(IOBuffer &Buffer) const {
    int numBytes;

    Buffer.Clear();

    string mSubscriptionId(subscriptionId, MAX_SUBSCRIPTION_ID);
    string mNewsAgencyId(newsAgencyId, MAX_NEWS_AGENCY_ID);
    string mMileage(mileage, MAX_MILEAGE);

    numBytes = Buffer.Pack(mSubscriptionId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mNewsAgencyId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(memberId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(mMileage.c_str());
    if ( numBytes == -1 ) return false;

    return true;
}
bool Subscription::Unpack(IOBuffer &Buffer) {
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(subscriptionId, MAX_SUBSCRIPTION_ID);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack(newsAgencyId, MAX_NEWS_AGENCY_ID);
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    memberId = buf;
    numBytes = Buffer.Unpack (mileage,MAX_MILEAGE);
    if ( numBytes == -1 ) return false;

    return true;
}
