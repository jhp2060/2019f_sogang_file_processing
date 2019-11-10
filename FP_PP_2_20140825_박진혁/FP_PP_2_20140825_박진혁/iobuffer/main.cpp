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
	while (1) {		// �л� �����͸� �о �ε����� ����
		Student s;
		int recaddr = StudentFile.Read (s);
		if (recaddr == -1) break;
		//Todo...
		cout << recaddr << '\n' << s;
	}
	StudentFile.Close ();

	// ������ �ε����� �ε��� ���Ϸ� ����
	//Todo...
	BufferFile StdIdxFile (//Todo...);
	StdIdxFile.Create ("fileOfStudent.ind", ios::out | ios::trunc);
	StdIdxFile.Rewind (); //��� ������ ù��° ���ڵ� ��ġ�� �̵�
	//Todo...
	int result = StdIdxFile.Write ();
	StdIdxFile.Close ();

	// TextIndexedFile�� ����Ͽ� �б� �� ����
	DelimFieldBuffer buf ('|', STDMAXBUF);
	//Todo...
	StdIdxedFile.Open ("fileOfStudent");

	Student s;
	StdIdxedFile.Read ("20121234", s);		// Ű�� ����Ͽ� �б�
	cout << s;

	StdIdxedFile.Read (s);	// ���� ���ڵ� �б�
	cout << s;

	Student s_new;
	s_new.update_id ("12345678");
	s_new.update_name ("HongGilDong");
	s_new.update_birthday ("1845/05/27");
	s_new.update_number ("010-1234-5678");
	StdIdxedFile.Append (s_new);	// ���ο� ���ڵ� �߰�
	StdIdxedFile.Read (s_new.Key (), s);	// �߰��� ���ڵ� �б�
	cout << s;

	StdIdxedFile.Close ();

	return 0;
}