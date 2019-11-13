#include "subscription_manager.h"

Subscription* SubscriptionManager::subscriptionSearch(string subscriptionId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Subscription> subscriptionFile(buf);
	subscriptionFile.Open(getDataFileName<Subscription>(), ios::in);

	Subscription* subscription = new Subscription();
	int recaddr = subscriptionFile.Read(*subscription);
	while (recaddr != -1 || buf.deletedRecaddr >= 0) {
		if (subscriptionId == string(subscription->subscriptionId, MAX_SUBSCRIPTION_ID - 1)) {
			subscriptionFile.Close();
			return subscription;
		}
		recaddr = subscriptionFile.Read(*subscription);
	}
	subscriptionFile.Close();
    return NULL;
}

void SubscriptionManager::subscriptionInsert() {
	Subscription newSubscription;
    char s[256];

    cout << "Input new subscription id (16 letters): "; 
    cin >> s;
	newSubscription.updateSubscriptionId(s);
	if (subscriptionSearch(s)) {
        cout << "There is same subscription with ID " << s << ".\n";
        return ;
	}
	else {
		cout << "Input new newsAgency ID (12 letters): ";
		cin >> s;
		newSubscription.updateNewsAgencyId(s);

		cout << "Input new member ID ";
		cin >> s;
		newSubscription.updateMemberId(s);

		cout << "Input new mileage (10 letters): ";
		cin >> s;
		newSubscription.updateMileage(s);

		saveSubscriptionRecord(newSubscription);
	}
}

void SubscriptionManager::subscriptionUpdate() {
	Subscription newSubscription;
    char s[256];

    cout << "Input subscription id to update (16 letters): "; 
    cin >> s;
	newSubscription.updateSubscriptionId(s);
	if (subscriptionSearch(s) == NULL) {
		cout << "There is no subscription to udpate with ID "
			<< string(s) << ".\n";
        return ;
	}
	else {
		subscriptionDelete(s);

		cout << "Input new newsAgency ID (12 letters): ";
		cin >> s;
		newSubscription.updateNewsAgencyId(s);

		cout << "Input new member ID : ";
		cin >> s;
		newSubscription.updateMemberId(s);

		cout << "Input new mileage (10 letters): ";
		cin >> s;
		newSubscription.updateMileage(s);

		saveSubscriptionRecord(newSubscription);
	}

}

void SubscriptionManager::subscriptionDelete(string subscriptionId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Subscription> subscriptionFile(buf);
	subscriptionFile.Open(getDataFileName<Subscription>(), ios::in | ios::out);
  	
	// linear serach
	Subscription curSubscription;
	int curRecaddr = subscriptionFile.Read(curSubscription);
	int prevRecaddr = curRecaddr;
	while (curRecaddr != -1 || buf.deletedRecaddr >= 0) {
		if (subscriptionId == string(curSubscription.subscriptionId, MAX_SUBSCRIPTION_ID - 1)) {
			
			// calculate the length of record to delete
			int recordLen = getSubscriptionRecordLen(curSubscription);

			// make the current subscription record as a dummy record
			makeDummySubscription(curSubscription, recordLen);
			subscriptionFile.Write(curSubscription, curRecaddr);

			//// merge the dummy record compartments (prev and cur)
			//Subscription prevSubscription;
			//subscriptionFile.Read(prevSubscription, prevRecaddr);

			//if (prevRecaddr != curRecaddr) { // subscription is not the first record
			//	// get previous Subscription record
			//	if (string(prevSubscription.subscriptionId,
			//		MAX_NEWS_AGENCY_ID - 1).find('*', 0) != string::npos) {
			//		// previous and current subscription record are a dummy record
			//		int prevLen = getSubscriptionRecordLen(prevSubscription);
			//		int curLen = getSubscriptionRecordLen(curSubscription);
			//		curRecaddr = prevRecaddr;
			//		// make new dummy record merging two dummy records
			//		makeDummySubscription(prevSubscription, prevLen + curLen);
			//		// merge two compartments and save it at prevRecaddr
			//		subscriptionFile.Write(prevSubscription, curRecaddr);
			//	}
			//}

			/* TO DO!! IMPLMENT MERGE OF CUR AND NEXT DUMMY RECORDS */

			subscriptionFile.Close();

			return;
		}
		prevRecaddr = curRecaddr;
		curRecaddr = subscriptionFile.Read(curSubscription);
	}
	subscriptionFile.Close();
	cout << "There is no subscription to delete with ID " << subscriptionId << ".\n";
	return;
}

void subscriptionDeleteWithMemberId(string memberId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Subscription> subscriptionFile(buf);
	subscriptionFile.Open(getDataFileName<Subscription>(), ios::in | ios::out);

	// linear serach
	Subscription curSubscription;
	int curRecaddr = subscriptionFile.Read(curSubscription);
	int prevRecaddr = curRecaddr;
	while (curRecaddr != -1 || buf.deletedRecaddr >= 0) {
		if (memberId == curSubscription.memberId) {
			// calculate the length of record to delete
			int recordLen = getSubscriptionRecordLen(curSubscription);

			// make the current subscription record as a dummy record
			makeDummySubscription(curSubscription, recordLen);
			if (buf.deletedRecaddr >= 0) curRecaddr = buf.deletedRecaddr;
			subscriptionFile.Write(curSubscription, curRecaddr);

			//// merge the dummy record compartments (prev and cur)
			//Subscription prevSubscription;
			//subscriptionFile.Read(prevSubscription, prevRecaddr);

			//if (prevRecaddr != curRecaddr) { // subscription is not the first record
			//	// get previous Subscription record
			//	if (string(prevSubscription.subscriptionId,
			//		MAX_NEWS_AGENCY_ID - 1).find('*', 0) != string::npos) {
			//		// previous and current subscription record are a dummy record
			//		int prevLen = getSubscriptionRecordLen(prevSubscription);
			//		int curLen = getSubscriptionRecordLen(curSubscription);
			//		curRecaddr = prevRecaddr;
			//		// make new dummy record merging two dummy records
			//		makeDummySubscription(prevSubscription, prevLen + curLen);
			//		// merge two compartments and save it at prevRecaddr
			//		subscriptionFile.Write(prevSubscription, curRecaddr);
			//	}
			//}

			/* TO DO!! IMPLMENT MERGE OF CUR AND NEXT DUMMY RECORDS */

			// keep searching
		}
		prevRecaddr = curRecaddr;
		curRecaddr = subscriptionFile.Read(curSubscription);
	}
	subscriptionFile.Close();
}

void subscriptionDeleteWithNewsAgencyId(string newsAgencyId) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Subscription> subscriptionFile(buf);
	subscriptionFile.Open(getDataFileName<Subscription>(), ios::in | ios::out);

	// linear serach
	Subscription curSubscription;
	int curRecaddr = subscriptionFile.Read(curSubscription);
	int prevRecaddr = curRecaddr;
	while (curRecaddr != -1 || buf.deletedRecaddr >= 0) {
		if (newsAgencyId == string(curSubscription.newsAgencyId, MAX_NEWS_AGENCY_ID - 1)) {

			// calculate the length of record to delete
			int recordLen = getSubscriptionRecordLen(curSubscription);

			// make the current subscription record as a dummy record
			makeDummySubscription(curSubscription, recordLen);
			subscriptionFile.Write(curSubscription, curRecaddr) << ' ';

			//// merge the dummy record compartments (prev and cur)
			//Subscription prevSubscription;
			//subscriptionFile.Read(prevSubscription, prevRecaddr);

			//if (prevRecaddr != curRecaddr) { // subscription is not the first record
			//	// get previous Subscription record
			//	if (string(prevSubscription.subscriptionId, 
			//		MAX_NEWS_AGENCY_ID - 1).find('*', 0) != string::npos) {
			//		// previous and current subscription record are a dummy record
			//		int prevLen = getSubscriptionRecordLen(prevSubscription);
			//		int curLen = getSubscriptionRecordLen(curSubscription);
			//		curRecaddr = prevRecaddr;
			//		// make new dummy record merging two dummy records
			//		makeDummySubscription(prevSubscription, prevLen + curLen);
			//		// merge two compartments and save it at prevRecaddr
			//		subscriptionFile.Write(prevSubscription, curRecaddr);
			//	}
			//}

			/* TO DO!! IMPLMENT MERGE OF CUR AND NEXT DUMMY RECORDS */

			// keep searching
		}
		prevRecaddr = curRecaddr;
		curRecaddr = subscriptionFile.Read(curSubscription, prevRecaddr);
	}
	subscriptionFile.Close();
}

int getSubscriptionRecordLen(Subscription s) {
	// a record start with a header(recordLen and a space)
	int ret = 2;
	ret += strlen(s.subscriptionId) + 1;
	ret += strlen(s.newsAgencyId) + 1;
	ret += s.memberId.length() + 1;
	ret += strlen(s.mileage) + 1;
	return ret;
}

void makeDummySubscription(Subscription &s, int deletedRecordLen) {
	// make dummy record
	string tmp = "";
	s.updateSubscriptionId("");
	s.updateNewsAgencyId("");

	// use variable length field
	s.updateMemberId(tmp);

	s.updateMileage("");
	deletedRecordLen -= getSubscriptionRecordLen(s);
	for (int i = 0; i < deletedRecordLen; i++) tmp += "*";
	s.updateMemberId(tmp);
}

void saveSubscriptionRecord(Subscription newSubscription) {
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<Subscription> subscriptionFile(buf);
	subscriptionFile.Open(getDataFileName<Subscription>(), ios::out);

	Subscription subscription;
	int recaddr = subscriptionFile.Read(subscription);
	while (true) {
		if (recaddr == -1 && buf.deletedRecaddr < 0) {
			// eof
			cout << subscriptionFile.Write(newSubscription) << "\n\n"; 
			cout << "Successfully saved the record!\n";
			subscriptionFile.Close();
			return;
		}
		else if (string(subscription.subscriptionId, MAX_SUBSCRIPTION_ID - 1).find('*', 0) != string::npos) {
			// found the vancant memory
			// TODO : calculate the size of vacant memory 
			//		  and find out it is enough to store this record
			int dummyLen = getSubscriptionRecordLen(subscription);
			int recordLen = getSubscriptionRecordLen(newSubscription);
			int delta = dummyLen - recordLen;
			if (delta >= MIN_SUBSCRIPTION_DUMMY_RECORD_LEN) {
				// make the rest of vacant memory as dummy record
				makeDummySubscription(subscription, delta);
				subscriptionFile.Write(subscription, recaddr);

				// save the new record at the dummy record(or deleted memory)
				subscriptionFile.Write(newSubscription, recaddr + delta);
				cout << "Successful saved the record!\n";
				return;
				subscriptionFile.Close();
			}
		}
		// get the address for next record;
		recaddr = subscriptionFile.Read(subscription);
	}
}


// project2
void SubscriptionManager::mySubscriptionInsert(string memberId) {
	NewsAgencyManager nm;
	Subscription newSubscription, *searchResult;
	NewsAgency *nmSearchResult;
	char s[256];

	cout << "Input new subscription id (16 letters): ";
	cin >> s;
	newSubscription.updateSubscriptionId(s);
	searchResult = subscriptionSearch(s);
	if (searchResult != NULL) {
		free(searchResult);
		cout << "There is same subscription with ID " << s << ".\n";
		return;
	}
	else {
		cout << "Input new newsAgency ID (12 letters): ";
		cin >> s;
		nmSearchResult = nm.newsAgencySearch(s);
		if (nmSearchResult == NULL) {
			cout << "There is no newsAgency with that ID.\n";
			return;
		}
		free(nmSearchResult);
		newSubscription.updateNewsAgencyId(s);

		newSubscription.updateMemberId(memberId);

		cout << "Input new mileage (10 letters): ";
		cin >> s;
		newSubscription.updateMileage(s);

		saveSubscriptionRecord(newSubscription);
	}
}


void SubscriptionManager::mySubscriptionUpdate(string memberId) {
	NewsAgencyManager nm;
	NewsAgency* newsAgency;
	Subscription newSubscription, *oldSubscription;
	char s[256];

	cout << "Input subscription id to update (16 letters): ";
	cin >> s;
	newSubscription.updateSubscriptionId(s);
	
	oldSubscription = subscriptionSearch(s);
	cout << *oldSubscription;
	if (oldSubscription == NULL || oldSubscription->memberId != memberId) {
		cout << "There is no subscription to update with ID "
			<< string(s) << ".\n";
		return;
	}
	else {
		subscriptionDelete(s);

		cout << "Input new newsAgency ID (12 letters): ";
		cin >> s;
		newsAgency = nm.newsAgencySearch(s);
		if (newsAgency == NULL) {
			cout << "There is no newsAgency with that ID.\n";
			return;
		}
		free(newsAgency);
		newSubscription.updateNewsAgencyId(s);

		newSubscription.updateMemberId(memberId);

		cout << "Input new mileage (10 letters): ";
		cin >> s;
		newSubscription.updateMileage(s);

		saveSubscriptionRecord(newSubscription);
	}

}

