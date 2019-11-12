#include "listFile.h"

// functions for generating new list txt file randomly!

void generateMemberList(int size) {
	ofstream ofs(getListFileName<Member>());

	string id;
	string password;
	string name;
	string phoneNumber;
	string address;
	char mileage[11];
	char level[2] = "9";

	srand(time(NULL));
	
	ofs << size << '\n';

	ofs << "TestUser" << '|' << "T1234" << '|' 
		<< "m_nm_-1" << '|'
		<< "010-" + generateRandomNumber(4)
		+ '-' + generateRandomNumber(4) << '|'
		<< "m_ad_-1" << '|'
		<< generateRandomNumber(10).c_str() << '|'
		<< "9\n";

	ofs << "admin" << '|' << "adminpass" << '|'
		<< "m_nm_0" << '|'
		<< "010-" + generateRandomNumber(4)
		+ '-' + generateRandomNumber(4) << '|'
		<< "m_ad_0" << '|'
		<< generateRandomNumber(10).c_str() << '|'
		<< "1\n";

	for (int i = 1; i <= size - 2; i++) {
		id = "m_id_" + to_string(i);
		password = "m_pw_" + to_string(i);
		name = "m_nm_" + to_string(i);
		phoneNumber = "010-" + generateRandomNumber(4)
			+ '-' + generateRandomNumber(4);
		address = "m_ad_" + to_string(i);
		strcpy(mileage, generateRandomNumber(10).c_str());
		ofs << id << '|' << password << '|' << name << '|'
			<< phoneNumber << '|' << address << '|'
			<< mileage << '|' << level << '\n';
	}


}

void generateNewsAgencyList(int size) {
	ofstream ofs(getListFileName<NewsAgency>());

	char newsAgencyId[13];
	string name;
	string address;
	
	ofs << size << '\n';
	for (int i = 1; i <= size; i++) {
		strcpy(newsAgencyId, intToString(i, 12).c_str());
		name = "n_nm_" + to_string(i);
		address = "n_ad_" + to_string(i);
		ofs << newsAgencyId << '|' << name << '|' << address << '\n';
	}

}

void generateSusbscriptionList(int size,
	int newsAgencySize, int memberSize) {
	ofstream ofs(getListFileName<Subscription>());

	char subscriptionId[17];
	char newsAgencyId[13];
	string memberId;
	char mileage[11];

	srand(time(NULL));

	ofs << size << '\n';
	for (int i = 1; i <= size; i++) {
		strcpy(subscriptionId, intToString(i, 16).c_str());
		strcpy(newsAgencyId,
			intToString((rand() % newsAgencySize) + 1, 12).c_str());
		memberId = "m_id_" + to_string((rand() % memberSize) + 1);
		strcpy(mileage, generateRandomNumber(10).c_str());
		ofs << subscriptionId << '|' << newsAgencyId << '|'
			<< memberId << '|' << mileage << '\n';
	}
}

string generateRandomNumber(int digit) {
	string ret = "";
	for (int i = 0; i < digit; i++) {
		ret += (char)((rand() % 10) + '0');
	}
	return ret;
}

string intToString(int integer, int digit) {
	string ret = "";
	char now;
	int iter = digit - 1;
	for (int i = 0; i < digit; i++) ret += "0";
	while (integer > 0) {
		now = (char)((integer % 10) + '0');
		ret[iter--] = now;
		integer /= 10;
	}
	return ret;
}
