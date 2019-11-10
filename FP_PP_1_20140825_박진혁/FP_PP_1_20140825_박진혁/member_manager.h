#ifndef __MEMBER_MANAGER_H__
#define __MEMBER_MANAGER_H__

#define MIN_MEMBER_DUMMY_RECORD_LEN (2 + 6 + 10)

#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "usingIOBuffer.h"
#include "./basic_class/member.h"
#include "./subscription_manager.h"
#include "listFile.h"

using namespace std;
class MemberManager {
public:
	bool memberSearch(string id);
	void memberInsert();
	void memberUpdate();
	void memberDelete(string id);
};

int getMemberRecordLen(Member m);
void makeDummyMember(Member &m, int deletedRecordLen);
void saveMemberRecord(Member newMember);

#endif
