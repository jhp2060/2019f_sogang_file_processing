#ifndef __NEWSAGENCY_H__
#define __NEWSAGENCY_H__

#include <string>
#include <cstring>
#include <sstream>

#include "Record.h"
#include "../usingIOBuffer.h"

using namespace std;

#define STDMAXBUF 256
#define MAX_NEWS_AGENCY_ID 12 + 1

class NewsAgency: public Record {
//class NewsAgency {
public:
	char newsAgencyId[MAX_NEWS_AGENCY_ID];
	string name;
	string address;

	// project 2
	string key;

public:
	NewsAgency() {}
	NewsAgency(const char * newNewsAgencyId) {
		updateNewsAgencyId(newNewsAgencyId);
	}
	NewsAgency(const NewsAgency& m);
	NewsAgency &operator = (const NewsAgency &n);
	bool operator == (const NewsAgency &n);
	bool operator != (const NewsAgency &n);
	void updateNewsAgencyId(const char * _newsAgencyId) {
		memcpy(newsAgencyId, _newsAgencyId, MAX_NEWS_AGENCY_ID);
	}
	void updateName(const string _name) { name = _name; }
	void updateAddress(const string _address) { address = _address; }

	friend istream & operator >> (istream &is, NewsAgency &n);
	friend ostream & operator << (ostream &is, NewsAgency &n);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer &Buffer);

	// project2
	char* Key();
};
istream & operator >> (istream &is, NewsAgency &n);
ostream & operator << (ostream &is, NewsAgency &n);

#endif
