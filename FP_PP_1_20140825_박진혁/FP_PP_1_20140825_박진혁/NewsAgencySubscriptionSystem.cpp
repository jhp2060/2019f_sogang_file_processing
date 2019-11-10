#include "NewsAgencySubscriptionSystem.h"

int main() {
	//generateMemberList(1000);
	//generateNewsAgencyList(1000);
	//generateSusbscriptionList(10000, 1000, 1000);

	while (true) {
        printMenu();
        int input;
		cin >> input;
		if (!(input >= 1 && input <= 19)) {
			cin.clear();
			cin.ignore(STDMAXBUF, '\n');
			cout << "Please enter the number between 1 and 19.\n";
			continue;
		}
		input = executeSystem(input);
		if (input == 0) {
			cout << "End system...\n";
			return 0;
		}
    }
    return 0;
}
void printMenu() {
    cout << " +=====================================+\n";
    cout << " |    NewsAgencySubscription System    |\n";
    cout << " |                                     |\n";
    cout << " |    Please enter the menu number!    |\n";
    cout << " +=====================================+\n";
    cout << " | 1. showMember                       |\n";
    cout << " | 2. showNewsAgency                   |\n";
    cout << " | 3. showSubscription                 |\n";
    cout << " | 4. MemberTest                       |\n";
    cout << " | 5. NewsAgencyTest                   |\n";
    cout << " | 6. SubscriptionTest                 |\n";
    cout << " | 7. SearchMember                     |\n";
    cout << " | 8. InsertMember                     |\n";
    cout << " | 9. UpdateMember                     |\n";
    cout << " | 10.DeleteMember                     |\n";
    cout << " | 11.SearchNewsAgency                 |\n";
    cout << " | 12.InsertNewsAgency                 |\n";
    cout << " | 13.UpdateNewsAgency                 |\n";
    cout << " | 14.DeleteNewsAgency                 |\n";
    cout << " | 15.SearchSubscription               |\n";
    cout << " | 16.InsertSubscription               |\n";
    cout << " | 17.UpdateSubscription               |\n";
    cout << " | 18.DeleteSubscription               |\n";
    cout << " | 19.END                              |\n";
    cout << " +=====================================+\n";
	cout << " 메뉴를 입력해주세요: ";
}

int executeSystem(int menu) {
    string s = "";
	MemberManager mm;
	NewsAgencyManager nm;
	SubscriptionManager sm;
    switch (menu) {
        case 1:
			showData<Member>();
            break;
        case 2:
			showData<NewsAgency>();
            break;
        case 3:
			showData<Subscription>();
            break;
        case 4:
            dataTest<Member>();
            break;
        case 5:
            dataTest<NewsAgency>();
            break;
        case 6:
            dataTest<Subscription>();
            break;
        case 7:
            cout << "Input member ID : ";
            cin >> s;
            mm.memberSearch(s);
            break;
        case 8:
            mm.memberInsert();
            break;
        case 9:
            mm.memberUpdate();
            break;
        case 10:
            cout << "Input delete member ID : ";
            cin >> s;
            mm.memberDelete(s);
            break;
        case 11:
            cout << "Input newsAgency ID (12 letters): ";
            cin >> s;
            nm.newsAgencySearch(s);
            break;
        case 12:
            nm.newsAgencyInsert();
            break;
        case 13:
            nm.newsAgencyUpdate();
            break;
        case 14:
            cout << "Input delete newsAgency ID (12 letters): ";
            cin >> s;
            nm.newsAgencyDelete(s);
            break;
        case 15:
            cout << "Input subscription ID (16 letters): ";
            cin >> s;
            sm.subscriptionSearch(s);
            break;
        case 16:
            sm.subscriptionInsert();
            break;
        case 17:
            sm.subscriptionUpdate();
            break;
        case 18:
            cout << "Input delete subscription ID (16 letters): ";
            cin >> s;
            sm.subscriptionDelete(s);
            break;
        case 19:
            return 0;
        default:
            return -1;
    }
	return 1;
}