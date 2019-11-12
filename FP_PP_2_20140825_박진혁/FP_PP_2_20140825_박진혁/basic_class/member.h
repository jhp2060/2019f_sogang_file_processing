#ifndef __MEMBER_H__	
#define __MEMBER_H__

#include <string>
#include <cstring>
#include <sstream>

#include "Record.h"
#include "../usingIOBuffer.h"
using namespace std;

#define MAX_MILEAGE 10 + 1
#define STDMAXBUF 256

class Member : public Record {
//class Member {
public:
	// project1
	string id;
	string password;
	string name;
	string phoneNumber;
	string address;
	char mileage[MAX_MILEAGE];

	// project2
	char level[2] = "1";
	string key;

public:
	// project1
	Member() {}
	Member(string newId) { updateId(newId); }
	Member(const Member& m);
	Member &operator = (const Member &m);
	bool operator == (const Member &m);
	bool operator != (const Member &m);
	void updateId(const string _id) { id = _id; }
	void updatePassword(const string _password) { password = _password; }
	void updateName(const string _name) { name = _name; }
	void updatePhoneNumber(const string _phoneNumber) {
		phoneNumber = _phoneNumber; 
	}
	void updateAddress(const string _address) { address = _address; }
	void updateMileage(const char *_mileage) {
		memcpy(mileage, _mileage, MAX_MILEAGE);
	}

	friend istream & operator >> (istream &is, Member &m);
	friend ostream & operator << (ostream &is, Member &m);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer &Buffer);

	// project2
	void updateLevel(const char* _level) { memcpy(level, _level, 2); };
	char* Key();
};

// project1
istream & operator >> (istream &is, Member &m);
ostream & operator << (ostream &is, Member &m);

#endif
