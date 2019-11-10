#ifndef __NEWS_AGENCY_SUBSCRIPTION_SYSTEM_H__
#define __NEWS_AGENCY_SUBSCRIPTION_SYSTEM_H__

#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "listFile.h"

#include "usingIOBuffer.h"
#include "./basic_class/member.h"
#include "./basic_class/newsAgency.h"
#include "./basic_class/subscription.h"
#include "member_manager.h"
#include "newsAgency_manager.h"
#include "subscription_manager.h"

void printMenu();
int executeSystem(int menu);

template <class T>
void showData() {
	ifstream ifs(getListFileName<T>());
	int n;

	ifs >> n;
	ifs.ignore(STDMAXBUF, '\n');

	for (int i = 0; i < 10; i++) {
		T data;
		ifs >> data;
		cout << data;
	}
	ifs.close();
}

template <class T>
void dataTest() {
	ifstream ifs(getListFileName<T>());
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<T> dataFile(buf);

	// renew the database and fill it with txt file
	dataFile.Create(getDataFileName<T>(), ios::out | ios::trunc);

	int count;
	ifs >> count;
	ifs.ignore(STDMAXBUF, '\n');

	for (int i = 0; i < count; i++) {
		T data;
		ifs >> data;
		if (dataFile.Write(data) == -1) {
			cout << "Write error in Test!\n";
			return;
		}
		if (i < 10) cout << data;
	}
	dataFile.Close();
	ifs.close();
}

#endif