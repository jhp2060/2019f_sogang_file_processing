#include "member_manager.h"

Member* MemberManager::memberSearch(string id) {
	
	// read member instance with index file
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member> memberIndexedFile(
		buf,
		getMaxRecordKeyLength<Member>(),
		getMaxRecordNumber<Member>()
	);
	memberIndexedFile.Open(getFileNameNoExtension<Member>(), ios::in);

	Member* member = new Member();
	member->updateId(id);
	
	// find member with key using Search and get the address
	if (memberIndexedFile.Read(member->Key(), *member) == -1) {
		memberIndexedFile.Close();
		return NULL;
	}
	else {
		memberIndexedFile.Close();
		return member;
	}
}

void MemberManager::memberInsert() {
	Member newMember;
	char s[256];

	// get new member record to insert
	cout << "Input new id : ";
	cin >> s;
	newMember.updateId(s);
	if (memberSearch(s) != NULL) {
		cout << "error : There is same member with ID " << s << ".\n";
		return;
	}
	else {
		cout << "Input new password : ";
		cin >> s;
		newMember.updatePassword(s);

		cout << "Input new name : ";
		cin >> s;
		newMember.updateName(s);

		cout << "Input new phoneNumber : ";
		cin >> s;
		newMember.updatePhoneNumber(s);

		cout << "Input new address : ";
		cin >> s;
		newMember.updateAddress(s);

		cout << "Input new mileage (10 letters): ";
		cin >> s;
		newMember.updateMileage(s);

		saveMemberRecord(newMember);
	}
}


void MemberManager::memberUpdate(string id) {
	Member newMember;
	char s[256];

	if (memberSearch(id) == NULL) {
		cout << "There is no member to update with ID " << id << ".\n";
		return;
	}
	else {
		newMember.updateId(id);
		memberDelete(id);

		cout << "Input new password : ";
		cin >> s;
		newMember.updatePassword(s);

		cout << "Input new name : ";
		cin >> s;
		newMember.updateName(s);

		cout << "Input new phoneNumber : ";
		cin >> s;
		newMember.updatePhoneNumber(s);

		cout << "Input new address : ";
		cin >> s;
		newMember.updateAddress(s);

		cout << "Input new mileage(10 letters): ";
		cin >> s;
		newMember.updateMileage(s);

		cout << "Input new level(1 or 9): ";
		cin >> s;
		newMember.updateLevel(s);

		saveMemberRecord(newMember);
	}
}

void MemberManager::memberDelete(string id) {
	/*
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Member> memberFile(buf);
	memberFile.Open(getDataFileName<Member>(), ios::in | ios::out);
	*/

	// read member instance with index file
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member> memberIndexedFile(
		buf,
		getMaxRecordKeyLength<Member>(),
		getMaxRecordNumber<Member>()
	);

	memberIndexedFile.Open(getFileNameNoExtension<Member>(), ios::in | ios::out);

	Member curMember;
	curMember.updateId(id);
	
	// get recaddr of curMember from .dat file
	int curRecaddr = memberIndexedFile.Read(curMember.Key(), curMember);
	int prevRecaddr = curRecaddr;
	int nextRecaddr;

	// no member to delete
	if (curRecaddr != -1) {
		cout << "There is no member to delete with that id.\n";
		return;
	}
	


	// make the member instance deleted
	// DO SOMETHING!


		//if (id == curMember.id) {
		//	// keeping reference integrity
		//	subscriptionDeleteWithMemberId(curMember.id);

		//	// calculate the length of record to delete
		//	int recordLen = getMemberRecordLen(curMember);

		//	// make the current member record as a dummy record
		//	makeDummyMember(curMember, recordLen);
		//	memberFile.Write(curMember, curRecaddr);


		//	///* MERGE VACANCIES INTO CURRENT VACANCY */
		//	/*bool isPrevDeleted = false;*/
		//	// merge the dummy record compartments (prev and cur)
		//	Member prevMember;
		//	memberFile.Read(prevMember, prevRecaddr);
		//	
		//	if (prevRecaddr != curRecaddr) { // member is not the first record
		//		// get previous Member record
		//		if (prevMember.id.find('*', 0) != string::npos) {
		//			// previous and current member record are a dummy record
		//			int prevLen = getMemberRecordLen(prevMember);
		//			int curLen = getMemberRecordLen(curMember);
		//			curRecaddr = prevRecaddr;
		//			// make new dummy record merging two dummy records
		//			makeDummyMember(prevMember, prevLen + curLen);
		//			// merge two compartments and save it at prevRecaddr
		//			memberFile.Write(prevMember, curRecaddr);
		//			// isPrevDeleted = true;
		//		}
		//	}

			//// merge the dummy record compartments (cur and next)
			//// get nextMember
			//Member nextMember;
			//int nextRecaddr = memberFile.Read(nextMember);
			//// not the first record && previous record is not deleted
			//if (!isPrevDeleted && prevRecaddr != curRecaddr) {
			//	nextRecaddr = memberFile.Read(nextMember);
			//}
			//if (nextRecaddr != -1) { // current Member is not a last record
			//	// get next Member record
			//	if (nextMember.id.find('*', 0) != string::npos) {
			//		// current and next member records are a dummy record
			//		int curLen = getMemberRecordLen(curMember);
			//		int nextLen = getMemberRecordLen(nextMember);
			//		makeDummyMember(curMember, curLen + nextLen);
			//		// merge two compartments and save it at curRecaddr
			//		memberFile.Write(curMember, curRecaddr);
			//	}
			//}

	//		memberFile.Close();
	//		cout << "Successful deletion of member with ID " << id << " .\n";
	//		return;
	//	}
	//	prevRecaddr = curRecaddr;
	//	curRecaddr = memberFile.Read(curMember);
	//}
	//memberFile.Close();
	//cout << "There is no member to delete with ID " << id << ".\n";
	//return;
}

int getMemberRecordLen(Member m) {
	// a record start with a header(recordLen and a space)
	int ret = 2;
	ret += m.id.length() + 1;
	ret += m.password.length() + 1;
	ret += m.name.length() + 1;
	ret += m.phoneNumber.length() + 1;
	ret += m.address.length() + 1;
	ret += strlen(m.mileage) + 1;
	ret += strlen(m.level) + 1;
	return ret;
}

void makeDummyMember(Member &m, int deletedRecordLen) {
	// make dummy record
	string tmp = "";
	// use variable length field to fill the vacancy
	m.updateId(tmp);
	m.updatePassword("");
	m.updateName("");
	m.updatePhoneNumber("");
	m.updateAddress("");
	m.updateMileage("");
	m.updateLevel("");
	deletedRecordLen -= getMemberRecordLen(m);
	for (int i = 0; i < deletedRecordLen; i++) tmp += "*";
	m.updateId(tmp);
}

void saveMemberRecord(Member newMember) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Member> memberFile(buf);
	memberFile.Open(getDataFileName<Member>(), ios::out);

	Member member;
	int recaddr = memberFile.Read(member);
	while (true) {
		if (recaddr == -1) {
			memberFile.Write(newMember);
			memberFile.Close();
			//cout << "Successfully saved the record!\n";
			return;
		}
		else if (member.id.find('*', 0) != string::npos) {
			// found the vancant memory
			// TODO : calculate the size of vacant memory 
			//		  and find out it is enough to store this record
			int dummyLen = getMemberRecordLen(member);
			int recordLen = getMemberRecordLen(newMember);
			int delta = dummyLen - recordLen;
			if (delta >= MIN_MEMBER_DUMMY_RECORD_LEN) {
				// make the rest of vacant memory as dummy record
				makeDummyMember(member, delta);
				memberFile.Write(member, recaddr);

				// save the new record at the dummy record(or deleted memory)
				memberFile.Write(newMember, recaddr + delta);
				//cout << "Successful saved the record!\n";
				memberFile.Close();
				return;
			}
		}
		// get the address for next record;
		recaddr = memberFile.Read(member);
	}
}
