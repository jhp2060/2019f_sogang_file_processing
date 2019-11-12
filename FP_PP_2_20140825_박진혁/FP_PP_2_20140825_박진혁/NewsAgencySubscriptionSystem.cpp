#include "NewsAgencySubscriptionSystem.h"

int main() {
	
	/*generateMemberList(1000);
	generateNewsAgencyList(1000);
	generateSusbscriptionList(10000, 1000, 1000);*/

	//// make .dat files
	//dataTest<Member>();
	//dataTest<NewsAgency>();
	//dataTest<Subscription>();

	// renew .ind files
	renewIndexFile<Member>();
	renewIndexFile<NewsAgency>();
	//renewIndexFile<Subscription>();

	char c_input;
	int input;
	
	Member* user = login();
	
	while (true) {
		if (user != NULL) break;
		cout << "Your ID or password is wrong.\n";
		cout << "Please recheck what you've entered.\n";
		cout << "Do you wanna try again? (y/n) : ";
		cin >> c_input;
		if (tolower(c_input) == 'n') {
			cout << "Exit NewsAgencySubscriptionSystem..\n";
			cout << "Now you're allowed to close the window.\n";
			return 0;
		}
		cin.clear();
		cin.ignore(STDMAXBUF, '\n');
		user = login();
	}
	if (strcmp(user->level, "1") == 0) {
		// admin user
		while (true) {
			cout << "\n+=====================================+\n";
			cout << "WELCOME! " << user->id << "!\n";
			printAdminMenu();
			cin >> input;
			if (input == 19) break;
			if (!(input >= 1 && input < 19)) {
				cin.clear();
				cin.ignore(STDMAXBUF, '\n');
				cout << "Please enter the number between 1 and 19.\n";
				continue;
			}
			executeAdminSystem(input, user);
		}
	}
	else if (strcmp(user->level, "9") == 0) {
		// normal user
		/*while (true) {
			cout << " WELCOME! " << user.id << "!\n";
			printNormalMenu();
			cin >> input;
			if (input == 8) break;
			if (!(input >= 1 && input < 8)) {
				cin.clear();
				cin.ignore(STDMAXBUF, '\n');
				cout << "Please enter the number between 1 and 19.\n";
				continue;
			}
			executeNormalSystem(input, user);
		}*/
	}
	cout << "Exit NewsAgencySubscriptionSystem..\n";
	cout << "Now you're allowed to close the window.\n";
    return 0;
}

// project2
Member* login() {
	string id;
	string password;
	Member* user;
	MemberManager mm;
	cout << "+=======================================+\n";
	cout << "Welcome to NewsAgencySubscription System!\n";
	cout << "Please login first.\n";
	cout << "Enter your ID : ";
	cin >> id;
	cout << "Enter your password : ";
	cin >> password;
	user = mm.memberSearch(id);
	if (user != NULL && user->password == password) {
		return user;
	}
	return NULL;
}

void printAdminMenu() {
	cout << "+=====================================+\n";
	cout << "|    NewsAgencySubscription System    |\n";
	cout << "|             ADMIN MODE              |\n";
	cout << "+=====================================+\n";
	cout << "| 1. showMember                       |\n";
	cout << "| 2. showNewsAgency                   |\n";
	cout << "| 3. showSubscription                 |\n";
	cout << "| 4. MemberTest                       |\n";
	cout << "| 5. NewsAgencyTest                   |\n";
	cout << "| 6. SubscriptionTest                 |\n";
	cout << "| 7. InsertMember                     |\n";
	cout << "| 8. UpdateMember                     |\n";
	cout << "| 9. DeleteMember                     |\n";
	cout << "| 10.SearchMember                     |\n";
	cout << "| 11.InsertNewsAgency                 |\n";
	cout << "| 12.UpdateNewsAgency                 |\n";
	cout << "| 13.DeleteNewsAgency                 |\n";
	cout << "| 14.SearchNewsAgency                 |\n";
	cout << "| 15.InsertSubscription               |\n";
	cout << "| 16.UpdateSubscription               |\n";
	cout << "| 17.DeleteSubscription               |\n";
	cout << "| 18.SearchSubscription               |\n";
	cout << "| 19.Quit                             |\n";
	cout << "+=====================================+\n";
	cout << "Please enter the menu number : ";
}

void executeAdminSystem(int menu, Member* admin) {
	MemberManager mm;
	NewsAgencyManager nm;
	SubscriptionManager sm;

	string s = "";
	
	Member* tmpMember;
	NewsAgency* tmpNewsAgency;
	Subscription* tmpSubscription;
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
		mm.memberInsert();
		break;
	case 8:
		cout << "Input member ID to update : ";
		cin >> s;
		mm.memberUpdate(s);
		break;
	case 9:
		cout << "Input member ID to delete : ";
		cin >> s;
		if (admin->id == s) {
			cout << "Cannot delete yourself in ADMIN mode\n";
			return;
		}
		mm.memberDelete(s);
		break;
	case 10:
		cout << "Input member ID : ";
		cin >> s;
		tmpMember = mm.memberSearch(s);
		if (tmpMember == NULL) cout << "No Member with that id.\n";
		else cout << *tmpMember;
		break;
	case 11:
		nm.newsAgencyInsert();
		break;
	case 12:
		nm.newsAgencyUpdate();
		break;
	case 13:
		cout << "Input delete newsAgency ID (12 letters): ";
		cin >> s;
		nm.newsAgencyDelete(s);
		break;
	case 14:
		cout << "Input newsAgency ID (12 letters): ";
		cin >> s;
		nm.newsAgencySearch(s);
		break;
	case 15:
		sm.subscriptionInsert();
		break;
	case 16:
		sm.subscriptionUpdate();
		break;
	case 17:
		cout << "Input delete subscription ID (16 letters): ";
		cin >> s;
		sm.subscriptionDelete(s);
		break;
	case 18:
		cout << "Input subscription ID (16 letters): ";
		cin >> s;
		sm.subscriptionSearch(s);
		break;
	default:
		return;
	}
}


void printNormalMenu() {
	cout << " +=====================================+\n";
	cout << " |    NewsAgencySubscription System    |\n";
	cout << " |                                     |\n";
	cout << " +=====================================+\n";
	cout << " | 1. UpdateMyInfo                     |\n";
	cout << " | 2. DeleteMyInfo(Withdraw)           |\n";
	cout << " | 3. SearchNewsAgency                 |\n";
	cout << " | 4. SearchMySubscription             |\n";
	cout << " | 5. InsertMySubscription(Register)   |\n";
	cout << " | 6. UpdateMySubscription             |\n";
	cout << " | 7. DeleteMySubscription             |\n";
	cout << " | 8. Quit                             |\n";
	cout << " +=====================================+\n";
	cout << " Please enter the menu number : ";
}
/*
void executeNormalSystem(int menu, Member* user){
	
	MemberManager mm;
	NewsAgencyManager nm;
	SubscriptionManager sm;

	string s = "";
	Subscription tmp;
	switch (menu) {
	case 1:
		mm.memberUpdate(user);
		break;
	case 2:
		cout << "Your informations will be deleted PERMANANTLY. ";
		cout << "Are you sure to withdraw? (y/n) : ";
		cin >> s;
		if (tolower(s[0]) == 'y') {
			mm.memberDelete(user.id);
		}
		break;
	case 3:
		cout << "Input newsAgency ID (12 letters): ";
		cin >> s;
		nm.newsAgencySearch(s);
		break;
	case 4:
		cout << "Input subscription ID (16 letters): ";
		cin >> s;
		tmp = sm.subscriptionSearch(s);
		if (tmp.memberId == user.id) {
			cout << tmp;
		}
		else {
			cout << "There is no subscription you find in your subscription list.\\n";
		}
		break;
	case 5:
		sm.subscriptionInsert();
		break;
	case 6:
		sm.subscriptionUpdate();
		break;
	case 7:
		cout << "Input delete subscription ID (16 letters): ";
		cin >> s;
		tmp = sm.subscriptionSearch(s);
		if (tmp.memberId == user.id) {
			cout << tmp;
		}
		else {
			cout << "There is no subscription you find in your subscription list.\\n";
		}
		break;
	case 8:
	default:
		return;
	}
}
*/