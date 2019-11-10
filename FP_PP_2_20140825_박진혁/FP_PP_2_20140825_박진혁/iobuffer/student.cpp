#include "student.h"
#include <sstream>

// 생성자
Student::Student () {
	// init...
}

Student::Student (const char * new_id) {
	update_id (new_id);
}

// 복사 생성자
Student::Student (const Student & s) {
	update_id (s.id);
	update_name (s.name);
	update_number (s.number);
	update_birthday (s.birthday);
}

// 객체 복사 연산자
Student & Student::operator = (const Student & s) {
	update_id (s.id);
	update_name (s.name);
	update_number (s.number);
	update_birthday (s.birthday);

	return *this;
}

// 같음
bool Student::operator == (const Student & s) {
	return !memcmp (id, s.id, 8);
}

// 다름
bool Student::operator != (const Student & s) {
	return 0 != memcmp (id, s.id, 8);
}

// 입력
istream & operator >> (istream & is, Student & s) {
	string st;

	is.exceptions (istream::failbit | istream::badbit);
	try {
		getline (is, st);
	} catch (istream::failure e) {
		// error
		return is;
	}

	istringstream iss (st);
	string token;

	getline (iss, token, '|');
	s.update_id (token.data ());
	getline (iss, token, '|');
	s.update_name (token);
	getline (iss, token, '|');
	s.update_number (token.data ());
	getline (iss, token, '|');
	s.update_birthday (token.data ());

	return is;
}

// 출력
ostream & operator << (ostream & os, Student & s) {
	string id (s.id, LENID);
	string number (s.number, LENNUM);
	string birthday (s.birthday, LENBIR);

	os << "ID : " << id << endl;
	os << "NAME : " << s.name << endl;
	os << "NUMBER : " << number << endl;
	os << "BIRTHDAY : " << birthday << endl;
	return os;
}

bool Student::Pack (IOBuffer & Buffer) const {
	int numBytes;
	
	Buffer.Clear ();
	
	string s_id (id, LENID);
	string s_number (number, LENNUM);
	string s_birthday (birthday, LENBIR);

	numBytes = Buffer.Pack (s_id.c_str ());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack (name.c_str ());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack (s_number.c_str ());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack (s_birthday.c_str ());
	if (numBytes == -1) return false;

	return true;
}

bool Student::Unpack (IOBuffer & Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack (id, LENID);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack (buf);
	if (numBytes == -1) return false;
	name = buf;
	numBytes = Buffer.Unpack (number, LENNUM);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack (birthday, LENBIR);
	if (numBytes == -1) return false;

	return true;
}