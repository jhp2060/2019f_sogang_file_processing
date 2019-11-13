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
	Member newMember, *searchResult;
	char s[256];

	// get new member record to insert
	cout << "Input new id : ";
	cin >> s;
	newMember.updateId(s);
	searchResult = memberSearch(s);
	if (searchResult != NULL) {
		cout << "There is same member with ID " << s << ".\n";
		free(searchResult);
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

		cout << "Input new level(1 or 9): ";
		cin >> s;
		newMember.updateLevel(s);

		saveMemberRecord(newMember);
	}
}


void MemberManager::memberUpdate(string id) {
	Member newMember, *searchResult;
	char s[256];

	searchResult = memberSearch(id);
	if (searchResult == NULL) {
		cout << "There is no member to update with ID " << id << ".\n";
		return;
	}
	else {
		free(searchResult);

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

		/*cout << "Input new level(1 or 9): ";
		cin >> s;
		newMember.updateLevel(s);*/

		saveMemberRecord(newMember);
	}
}

void MemberManager::memberDelete(string id) {

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

	// no member to delete
	if (curRecaddr == -1) {
		cout << "There is no member to delete with that id.\n";
		return;
	}
	
	// keep reference integrity
	//subscriptionDeleteWithMemberId(curMember.id);
	
	// delete record from .dat & remove record from Index
	memberIndexedFile.Delete(curRecaddr);
	memberIndexedFile.Remove(curMember);

	memberIndexedFile.Close();
	return;
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
	TextIndexedFile<Member> memberIndexedFile(
		buf,
		getMaxRecordKeyLength<Member>(),
		getMaxRecordNumber<Member>()
	);

	memberIndexedFile.Open(getFileNameNoExtension<Member>(), ios::in | ios::out);

	Member member;
	int recaddr;
	int recordLen = getMemberRecordLen(newMember);

	// linear search
	while (true) {
		if (memberIndexedFile.Read(member) == -1) {
			if (buf.SizeOfBuffer() < 0) {
				// append to the last of .dat file
				memberIndexedFile.Append(newMember);
				memberIndexedFile.Close();
				return;
			}
			else if (buf.SizeOfBuffer() + 2 >= recordLen + MIN_MEMBER_DUMMY_RECORD_LEN) {
				// check the deleted data space
				int delta = buf.SizeOfBuffer() + 2 - recordLen;

				memberIndexedFile.Write(newMember, buf.deletedRecaddr);
				memberIndexedFile.Insert(newMember.Key(), buf.deletedRecaddr);

				makeDummyMember(member, delta);
				memberIndexedFile.Write(member, -1);

				memberIndexedFile.Close();
				//cout << "Successfully saved the record!\n";
				return;
			}
		}
	}
}
