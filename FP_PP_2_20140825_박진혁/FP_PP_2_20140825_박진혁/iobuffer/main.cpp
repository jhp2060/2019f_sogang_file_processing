#include "student.h"
#include "recfile.h"
#include "textind.h"
#include "indfile.h"
#include "buffile.h"
#include <fstream>
#include <vector>

using namespace std;

int main () {
	DelimFieldBuffer buffer ('|', STDMAXBUF);
	RecordFile <Student> StudentFile (buffer);

	//Todo...
	
	StudentFile.Open ("fileOfStudent.dat", ios::in);
	while (1) {		// 학생 데이터를 읽어서 인덱스를 생성
		Student s;
		int recaddr = StudentFile.Read (s);
		if (recaddr == -1) break;
		//Todo...
		cout << recaddr << '\n' << s;
	}
	StudentFile.Close ();

	// 생성한 인덱스를 인덱스 파일로 저장
	//Todo...
	BufferFile StdIdxFile (//Todo...);
	StdIdxFile.Create ("fileOfStudent.ind", ios::out | ios::trunc);
	StdIdxFile.Rewind (); //헤더 다음의 첫번째 레코드 위치로 이동
	//Todo...
	int result = StdIdxFile.Write ();
	StdIdxFile.Close ();

	// TextIndexedFile을 사용하여 읽기 및 쓰기
	DelimFieldBuffer buf ('|', STDMAXBUF);
	//Todo...
	StdIdxedFile.Open ("fileOfStudent");

	Student s;
	StdIdxedFile.Read ("20121234", s);		// 키를 사용하여 읽기
	cout << s;

	StdIdxedFile.Read (s);	// 다음 레코드 읽기
	cout << s;

	Student s_new;
	s_new.update_id ("12345678");
	s_new.update_name ("HongGilDong");
	s_new.update_birthday ("1845/05/27");
	s_new.update_number ("010-1234-5678");
	StdIdxedFile.Append (s_new);	// 새로운 레코드 추가
	StdIdxedFile.Read (s_new.Key (), s);	// 추가한 레코드 읽기
	cout << s;

	StdIdxedFile.Close ();

	return 0;
}