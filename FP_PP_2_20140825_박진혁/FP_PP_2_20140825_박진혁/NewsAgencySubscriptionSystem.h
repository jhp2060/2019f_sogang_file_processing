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

// project2
Member* login();
void printAdminMenu();
void executeAdminSystem(int menu, Member* admin);
void printNormalMenu();
void executeNormalSystem(int menu, Member* user);


// project 1 
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


template <class RecType>
void dataTest() {
	ifstream ifs(getListFileName<RecType>());
	DelimFieldBuffer buf('|', STDMAXBUF);
	RecordFile<RecType> dataFile(buf);

	// renew the database and fill it with txt file
	dataFile.Create(getDataFileName<RecType>(), ios::out | ios::trunc);

	int count;
	ifs >> count;
	ifs.ignore(STDMAXBUF, '\n');

	for (int i = 0; i < count; i++) {
		RecType data;
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

// project2
template <class RecType>
void renewIndexFile() {
	// make .ind file with .dat file
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <RecType> recordFile(buffer);
	TextIndex recordIndex(getMaxRecordNumber<RecType>());
	recordFile.Open(getDataFileName<RecType>(), ios::in);
	while (true) {
		RecType record;
		int recaddr = recordFile.Read(record);
		if (recaddr == -1) break;
		recordIndex.Insert(record.Key(), recaddr);
	}
	recordFile.Close();

	TextIndexBuffer indexBuffer(getMaxRecordKeyLength<RecType>(), getMaxRecordNumber<RecType>());
	BufferFile recordBufferFile(indexBuffer);
	recordBufferFile.Create(getIndexFileName<RecType>(), ios::out | ios::trunc);
	recordBufferFile.Rewind();

	indexBuffer.Pack(recordIndex);
	recordBufferFile.Write();
	recordBufferFile.Close();
}

#endif