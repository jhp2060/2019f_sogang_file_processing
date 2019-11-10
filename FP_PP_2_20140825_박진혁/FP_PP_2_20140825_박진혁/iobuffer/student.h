#include <iostream>
#include <string>
#include "delim.h"

#define LENID	8
#define LENNUM	13
#define LENBIR	10
#define STDMAXBUF	256

using namespace std;

class Student {
	char id[LENID];
	string name;
	char number[LENNUM];
	char birthday[LENBIR];

public:
	Student ();	// 생성자
	Student (const char * new_id);
	Student (const Student & s);	// 복사 생성자

	Student & operator = (const Student & s);	// 객체 복사 연산자
	bool operator == (const Student & s);	// 같음 비교
	bool operator != (const Student & s);	// 다름 비교

	friend istream & operator >> (istream & is, Student & s);	// 입력
	friend ostream & operator << (ostream & os, Student & s);	// 출력

	// 업데이트
	void update_id (const char * new_id) { memcpy (id, new_id, LENID); }
	void update_name (string new_name) { name = new_name; }
	void update_number (const char * new_number) { memcpy (number, new_number, LENNUM); }
	void update_birthday (const char * new_birthday) { memcpy (birthday, new_birthday, LENBIR); }

	bool Pack (IOBuffer & Buffer) const;
	bool Unpack (IOBuffer &);
};

// 입, 출력 스트림
istream & operator >> (istream & is, Student & s);
ostream & operator << (ostream & os, Student & s);