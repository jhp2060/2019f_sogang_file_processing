#include "newsAgency_manager.h"

bool NewsAgencyManager::newsAgencySearch(string newsAgencyId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<NewsAgency> newsAgencyFile(buf);
	newsAgencyFile.Open(getDataFileName<NewsAgency>(), ios::in);

	NewsAgency newsAgency;
	int recaddr = newsAgencyFile.Read(newsAgency);
	// linear serach
	while (recaddr != -1) {
		if (newsAgencyId == string(newsAgency.newsAgencyId, MAX_NEWS_AGENCY_ID - 1)) {
			cout << newsAgency;
			newsAgencyFile.Close();
			return true;
		}
		recaddr = newsAgencyFile.Read(newsAgency);
	}
	newsAgencyFile.Close();
	cout << "There is no newsAgency with ID " << newsAgencyId << ".\n";
	return false;
}


void NewsAgencyManager::newsAgencyInsert() {
	NewsAgency newNewsAgency;
	char s[256];

	// get new newsAgency record to insert
	cout << "Input new NewsAgecnyId (12 letters): ";
	cin >> s;
	newNewsAgency.updateNewsAgencyId(s);
	if (newsAgencySearch(s)) {
		cout << "error : There is same newsAgency with ID " << s << ".\n";
		return;
	}
	else {
		cout << "Input new name : ";
		cin >> s;
		newNewsAgency.updateName(s);

		cout << "Input new address : ";
		cin >> s;
		newNewsAgency.updateAddress(s);

		saveNewsAgencyRecord(newNewsAgency);
	}
}

void NewsAgencyManager::newsAgencyUpdate() {
	NewsAgency newNewsAgency;
    char s[256];

    cout << "Input newsAgency id (12 letters): "; 
    cin >> s;
	newNewsAgency.updateNewsAgencyId(s);
	if (!newsAgencySearch(s)) {
        cout << "There is no newsAgency to update with ID " << string(s) << ".\n";
        return ;
    } else {
        newsAgencyDelete(s);

        cout << "Input new name : ";
		cin >> s;
		newNewsAgency.updateName(s);

        cout << "Input new address : ";
        cin >> s;
		newNewsAgency.updateAddress(s);

		saveNewsAgencyRecord(newNewsAgency);	
	}
}
void NewsAgencyManager::newsAgencyDelete(string newsAgencyId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<NewsAgency> newsAgencyFile(buf);
	newsAgencyFile.Open(getDataFileName<NewsAgency>(), ios::in | ios::out);

	// linear serach
	NewsAgency curNewsAgency;
	int curRecaddr = newsAgencyFile.Read(curNewsAgency);
	int prevRecaddr = curRecaddr;
	while (curRecaddr != -1) {
		if (newsAgencyId == string(curNewsAgency.newsAgencyId, MAX_NEWS_AGENCY_ID - 1)) {
			// keeping reference integrity
			subscriptionDeleteWithNewsAgencyId(string(curNewsAgency.newsAgencyId, MAX_NEWS_AGENCY_ID - 1));

			// calculate the length of record to delete
			int recordLen = getNewsAgencyRecordLen(curNewsAgency);

			// make the current newsAgency record as a dummy record
			makeDummyNewsAgency(curNewsAgency, recordLen);
			newsAgencyFile.Write(curNewsAgency, curRecaddr);

			// merge the dummy record compartments (prev and cur)
			NewsAgency prevNewsAgency;
			newsAgencyFile.Read(prevNewsAgency, prevRecaddr);
			
			if (prevRecaddr != curRecaddr) { // newsAgency is not the first record
				// get previous NewsAgency record
				if (string(prevNewsAgency.newsAgencyId, MAX_NEWS_AGENCY_ID - 1).find('*', 0) 
					!= string::npos) {
					// previous and current newsAgency record are a dummy record
					int prevLen = getNewsAgencyRecordLen(prevNewsAgency);
					int curLen = getNewsAgencyRecordLen(curNewsAgency);
					curRecaddr = prevRecaddr;
					// make new dummy record merging two dummy records
					makeDummyNewsAgency(prevNewsAgency, prevLen + curLen);
					// merge two compartments and save it at prevRecaddr
					newsAgencyFile.Write(prevNewsAgency, curRecaddr);
				}
			}

			/* TO DO!! IMPLMENT MERGE OF CUR AND NEXT DUMMY RECORDS */

			newsAgencyFile.Close();
			cout << "Successful deletion of newsAgency with ID " << newsAgencyId << " .\n";

			return;
		}
		prevRecaddr = curRecaddr;
		curRecaddr = newsAgencyFile.Read(curNewsAgency);
	}
	newsAgencyFile.Close();
	cout << "There is no newsAgency to delete with ID " << newsAgencyId << ".\n";
	return;

}

int getNewsAgencyRecordLen(NewsAgency n) {
	// a record start with a header(recordLen and a space)
	// length including '|' and header
	int ret = 2;
	ret += strlen(n.newsAgencyId) + 1;
	ret += n.name.length() + 1;
	ret += n.address.length() + 1;
	return ret;

}
void makeDummyNewsAgency(NewsAgency &n, int deletedRecordLen) {
	// make dummy record
	string tmp = "";
	n.updateNewsAgencyId("************\0");
	// use varialbe length field to fill the vacancy
	n.updateName(tmp);
	n.updateAddress("");
	deletedRecordLen -= getNewsAgencyRecordLen(n);
	for (int i = 0; i < deletedRecordLen; i++) tmp += "*";
	n.updateName(tmp);
}

void saveNewsAgencyRecord(NewsAgency newNewsAgency) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<NewsAgency> newsAgencyFile(buf);
	newsAgencyFile.Open(getDataFileName<NewsAgency>(), ios::out);

	NewsAgency newsAgency;
	int recaddr = newsAgencyFile.Read(newsAgency);
	while (true) {
		if (recaddr == -1) {
			newsAgencyFile.Write(newNewsAgency);
			newsAgencyFile.Close();
			cout << "Successfully saved the record!\n";
			return;
		}
		else if (string(newsAgency.newsAgencyId, 
			MAX_NEWS_AGENCY_ID - 1).find('*', 0) != string::npos) {
			// found the vancant memory
			// TODO : calculate the size of vacant memory 
			//		  and find out it is enough to store this record
			int dummyLen = getNewsAgencyRecordLen(newsAgency);
			int recordLen = getNewsAgencyRecordLen(newNewsAgency);
			int delta = dummyLen - recordLen;
			if (delta >= MIN_NEWS_AGENCY_DUMMY_RECORD_LEN) {
				// make the rest of vacant memory as dummy record
				makeDummyNewsAgency(newsAgency, delta);
				newsAgencyFile.Write(newsAgency, recaddr);

				// save the new record at the dummy record(or deleted memory)
				newsAgencyFile.Write(newNewsAgency, recaddr + delta);
				cout << "Successful saved the record!\n";
				newsAgencyFile.Close();
				return;
			}
		}
		// get the address for next record;
		recaddr = newsAgencyFile.Read(newsAgency);
	}
}
