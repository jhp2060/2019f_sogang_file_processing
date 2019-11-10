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
	Student ();	// ������
	Student (const char * new_id);
	Student (const Student & s);	// ���� ������

	Student & operator = (const Student & s);	// ��ü ���� ������
	bool operator == (const Student & s);	// ���� ��
	bool operator != (const Student & s);	// �ٸ� ��

	friend istream & operator >> (istream & is, Student & s);	// �Է�
	friend ostream & operator << (ostream & os, Student & s);	// ���

	// ������Ʈ
	void update_id (const char * new_id) { memcpy (id, new_id, LENID); }
	void update_name (string new_name) { name = new_name; }
	void update_number (const char * new_number) { memcpy (number, new_number, LENNUM); }
	void update_birthday (const char * new_birthday) { memcpy (birthday, new_birthday, LENBIR); }

	bool Pack (IOBuffer & Buffer) const;
	bool Unpack (IOBuffer &);
};

// ��, ��� ��Ʈ��
istream & operator >> (istream & is, Student & s);
ostream & operator << (ostream & os, Student & s);