#include "member.h"

Member::Member(const Member &m) {
    updateId(m.id);
    updatePassword(m.password);
    updateName(m.name);
    updatePhoneNumber(m.phoneNumber);
    updateAddress(m.address);
    updateMileage(m.mileage);

	//project2
	updateLevel(m.level);
}

Member &Member::operator = (const Member &m) {
    updateId(m.id);
    updatePassword(m.password);
    updateName(m.name);
    updatePhoneNumber(m.phoneNumber);
    updateAddress(m.address);
    updateMileage(m.mileage);
	
	// project2
	updateLevel(m.level);

    return *this;
}
bool Member::operator == (const Member &m) {
    return (id == m.id);
}

bool Member::operator != (const Member &m) {
    return (id != m.id);
}

istream & operator >> (istream &is, Member &m) {
    string s;
    is.exceptions(istream::failbit | istream::badbit);

    try {
        getline(is,s);
    } catch (istream::failure e) {
        return is;
    }

    istringstream iss(s);
    string token;

    getline(iss, token, '|');
    m.updateId(token);
    getline(iss, token, '|');
    m.updatePassword(token);
    getline(iss, token, '|');
    m.updateName(token);
    getline(iss, token, '|');
    m.updatePhoneNumber(token);
    getline(iss, token, '|');
    m.updateAddress(token);
    getline(iss, token, '|');
    m.updateMileage(token.data());

	// project2
	getline(iss, token, '|');
	m.updateLevel(token.data());

    return is;
}

ostream & operator << (ostream &os, Member &m) {
    string mMileage (m.mileage, MAX_MILEAGE);

    os << "ID : " << m.id << endl;
    os << "PASSWORD : " << m.password << endl;
    os << "NAME : " << m.name << endl;
    os << "PHONE NUMBER : " << m.phoneNumber << endl;
    os << "ADDRESS : " << m.address << endl;
    os << "MILEAGE : " << mMileage << endl;

	// project2
	// default level of member is "1"
    
    return os; 
}
bool Member::Pack(IOBuffer &Buffer) const {
	// store the data of Member instace into Buffer
    int numBytes;

    Buffer.Clear();

    numBytes = Buffer.Pack(id.c_str());
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Pack(password.c_str());
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Pack(name.c_str());
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Pack(phoneNumber.c_str());
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Pack(address.c_str());
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Pack(mileage);
    if ( numBytes == -1 ) return false;

	// project2
	numBytes = Buffer.Pack(level);
	if ( numBytes == -1 ) return false;

    return true;
}
bool Member::Unpack(IOBuffer &Buffer) {
	// get the whole data from Buffer
	// and seperate the whole data with delimeter
	// and those seperated data will be each field's value
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    id = buf;

    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    password = buf;

	numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    name = buf; 

	numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    phoneNumber = buf;

	numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    address = buf; 

	// no need of using buf cuz mileage is also char*
    numBytes = Buffer.Unpack(mileage, MAX_MILEAGE);
    if ( numBytes == -1 ) return false;

	// project2
	numBytes = Buffer.Unpack(level, 2);
	if (numBytes == -1) return false;

    return true;
}

// project2
char* Member::Key() {
	key.assign(id);
	return (char*)(key.c_str());
}
