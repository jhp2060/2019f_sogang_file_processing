#include "newsAgency_manager.h"

NewsAgency* NewsAgencyManager::newsAgencySearch(string newsAgencyId) {

	// read newsAgency instance with index file
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<NewsAgency> newsAgencyIndexedFile(
		buf,
		getMaxRecordKeyLength<NewsAgency>(),
		getMaxRecordNumber<NewsAgency>()
	);
	newsAgencyIndexedFile.Open(getFileNameNoExtension<NewsAgency>(), ios::in);

	NewsAgency* newsAgency = new NewsAgency();
	newsAgency->updateNewsAgencyId(newsAgencyId.c_str());

	// find newsAgency with key using Search and get the address
	if (newsAgencyIndexedFile.Read(newsAgency->Key(), *newsAgency) == -1) {
		free(newsAgency);
		newsAgencyIndexedFile.Close();
		return NULL;
	}
	else {
		newsAgencyIndexedFile.Close();
		return newsAgency;
	}
}


void NewsAgencyManager::newsAgencyInsert() {
	NewsAgency newNewsAgency, *searchResult;
	char s[256];

	// get new newsAgency record to insert
	cout << "Input new NewsAgecnyId (12 letters): ";
	cin >> s;
	newNewsAgency.updateNewsAgencyId(s);

	searchResult = newsAgencySearch(s);
	if (searchResult != NULL) {
		cout << "There is same newsAgency with ID " << s << ".\n";
		free(searchResult);
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

void NewsAgencyManager::newsAgencyUpdate(string newsAgencyId) {
	NewsAgency newNewsAgency, *searchResult;
    char s[256];

	newNewsAgency.updateNewsAgencyId(newsAgencyId.c_str());
	searchResult = newsAgencySearch(s);
	if (searchResult == NULL) {
        cout << "There is no newsAgency to update with ID " << newsAgencyId << ".\n";
        return ;
    } else {
		free(searchResult);
		
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
	// read newsAgency instance with index file
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<NewsAgency> newsAgencyIndexedFile(
		buf,
		getMaxRecordKeyLength<NewsAgency>(),
		getMaxRecordNumber<NewsAgency>()
	);

	newsAgencyIndexedFile.Open(getFileNameNoExtension<NewsAgency>(), ios::in | ios::out);

	NewsAgency curNewsAgency;
	curNewsAgency.updateNewsAgencyId(newsAgencyId.c_str());

	// get recaddr of curNewsAgency from .dat file
	int curRecaddr = newsAgencyIndexedFile.Read(curNewsAgency.Key(), curNewsAgency);

	// no newsAgency to delete
	if (curRecaddr == -1) {
		cout << "There is no newsAgency to delete with that id.\n";
		return;
	}

	//subscriptionDeleteWithNewsAgencyId(string(curNewsAgency.newsAgencyId, MAX_NEWS_AGENCY_ID - 1));

	// delete record from .dat & remove record from Index
	newsAgencyIndexedFile.Delete(curRecaddr);
	newsAgencyIndexedFile.Remove(curNewsAgency);

	newsAgencyIndexedFile.Close();
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
	n.updateNewsAgencyId("");
	// use varialbe length field to fill the vacancy
	n.updateName(tmp);
	n.updateAddress("");
	deletedRecordLen -= getNewsAgencyRecordLen(n);
	for (int i = 0; i < deletedRecordLen; i++) tmp += "*";
	n.updateName(tmp);
}

void saveNewsAgencyRecord(NewsAgency newNewsAgency) {
	// read newsAgency instance with index file
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<NewsAgency> newsAgencyIndexedFile(
		buf,
		getMaxRecordKeyLength<NewsAgency>(),
		getMaxRecordNumber<NewsAgency>()
	);

	newsAgencyIndexedFile.Open(getFileNameNoExtension<NewsAgency>(), ios::in | ios::out);

	NewsAgency newsAgency;
	int recaddr;
	int recordLen = getNewsAgencyRecordLen(newNewsAgency);

	while (true) {
		if (newsAgencyIndexedFile.Read(newsAgency) == -1) {
			if (buf.SizeOfBuffer() < 0) {
				// append to the last of .dat file
				newsAgencyIndexedFile.Append(newNewsAgency);
				newsAgencyIndexedFile.Close();
				return;
			}
			else if (buf.SizeOfBuffer() + 2 >= recordLen + MIN_NEWS_AGENCY_DUMMY_RECORD_LEN) {
				// check the deleted data space
				int delta = buf.SizeOfBuffer() + 2 - recordLen;

				newsAgencyIndexedFile.Write(newNewsAgency, buf.deletedRecaddr);
				newsAgencyIndexedFile.Insert(newNewsAgency.Key(), buf.deletedRecaddr);

				makeDummyNewsAgency(newsAgency, delta);
				newsAgencyIndexedFile.Write(newsAgency, -1);

				newsAgencyIndexedFile.Close();
				//cout << "Successfully saved the record!\n";
				return;
			}
		}
	}
}
