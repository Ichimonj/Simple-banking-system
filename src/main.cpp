#include<iostream>
#include"Client.h"
#include"Transactions.h"
#include"UserBase.h"
#include<fstream>
#include<Windows.h>

using namespace std;

int base_interfase();
void user_interfase(Client* client);
void change_profile(Client* client);
void transactions(Client* client);

Client* createUser() {
	string name;
	string surname;
	string patromymic;
	string phoneNumber;
	string pasword;
	Date DB;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your surname: ";
	cin >> surname;
	cout << "Enter your patromymic: ";
	cin >> patromymic;
	cout << "Enter your phone number: ";
	cin >> phoneNumber;
	cout << "Enter date berth:\n";
	DB = createDate(0,0,0);
	cout << "Enter pasword: ";
	cin >> pasword;
	
	system("cls");
	Client temp(name, surname, patromymic, phoneNumber,pasword, DB);
	UserBase::addClient(temp);
	user_interfase(UserBase::findUser(phoneNumber));
	return UserBase::findUser(phoneNumber);
}

void user_interfase(Client* client) {
	char ch = '0';
	while (strchr("123", ch) == nullptr) {
		system("cls");
		cout << *client << endl;
		cout << "1 - Change profile\n2 - Transactions\n3 - Exit\n";
		cin >> ch;
		system("cls");
	}
	if (ch == '1') {
		system("cls");
		change_profile(client);
	}
	else if (ch == '2') {
		system("cls");
		transactions(client);
	}
	else if (ch == '3') {
		system("cls");
		base_interfase();
	}
}
void transactions(Client* client) {
	bool is_true = true;
	while (is_true) {
		char ch = '0';
		while (strchr("12345", ch) == nullptr) {
			system("cls");
			cout << *client << endl;
			cout << "1 - Create new card\n2 - Top up the card\n3 - Write off from card\n4 - Transfer to card\n5 - Exit\n";
			cin >> ch;
		}if (ch == '1') {
			client->createNewCard();
		}
		else if (ch == '2') {
			if (client->get_size_cards() == 0) {
				system("cls");
				cout << "You don't have cards yet";
				Sleep(1000);
			}
			else {
				int cardId = 11;
				while (cardId <= 0 || cardId > client->get_size_cards()) {
					system("cls");
					cout << "Enter card id: ";
					cin >> cardId;
				}
				system("cls");
				cout << "Enter amount(dollar cent): ";
				int dollar, cent;
				cin >> dollar >> cent;
				Transactions::replenish(client->returnCard(cardId), dollar, cent);
			}
		}
		else if (ch == '3') {
			if (client->get_size_cards() == 0) {
				system("cls");
				cout << "You don't have cards yet";
				Sleep(1000);
			}
			else {
				int cardId = 11;
				while (cardId <= 0 || cardId > client->get_size_cards()) {
					system("cls");
					cout << "Enter card id: ";
					cin >> cardId;
				}
				system("cls");
				cout << "Enter amount(dollar cent): ";
				int dollar, cent;
				cin >> dollar >> cent;
				Transactions::withdrawal(client->returnCard(cardId), dollar, cent);
			}
		}
		else if (ch == '4') {
			if (client->get_size_cards() == 0) {
				system("cls");
				cout << "You don't have cards yet";
				Sleep(1000);
			}
			else {
				int cardId = 11;
				while (cardId <= 0 || cardId > client->get_size_cards()) {
					system("cls");
					cout << "Enter card id: ";
					cin >> cardId;
				}
				cout << "Enter the card number for transfer: ";
				string cardnumber;
				cin >> cardnumber;
				Card *transfer = CardBase::find_card(cardnumber);
				if (transfer == nullptr) {
					system("cls");
					cout << "Card not found";
					Sleep(1000);
					system("cls");
				}
				else {
					cout << "Enter amount(dollar cent): ";
					int dollar, cent;
					cin >> dollar >> cent;
					Transactions::translation(client->returnCard(cardId), *transfer, dollar, cent);
				}

			}
		}
		else if (ch == '5') {
			is_true = false;
		}
	}
	user_interfase(client);
}
void change_profile(Client*client) {
	bool is_true = true;
	while (is_true)
	{
		char ch = '0';
		while (strchr("123456", ch) == nullptr) {
			system("cls");
			cout << *client << endl;
			cout << "1 - Change name\n2 - Change surname\n3 - Change patronymic\n4 - Change date of birth\n5 - Change pasword\n6 - Exit\n";
			cin >> ch;
		}
		if (ch == '1') {
			system("cls");
			string name;
			cout << "Enter name: ";
			cin >> name;
			client->set_name(name);
		}
		else if (ch == '2') {
			system("cls");
			string surname;
			cout << "Enter surname: ";
			cin >> surname;
			client->set_surname(surname);
		}
		else if (ch == '3') {
			system("cls");
			string patronymic;
			cout << "Enter patronymic: ";
			cin >> patronymic;
			client->set_patronymic(patronymic);
		}
		else if (ch == '4') {
			system("cls");
			client->set_berth();
		}
		else if (ch == '5') {
			system("cls");
			cout << "Enter old password: ";
			string password;
			cin >> password;
			while (to_string(hash<string>{}(password)) != client->get_password()) {
				system("cls");
				cout << "The password was entered incorrectly\nEnter the correct password\n1 - Exit\n";
				cin >> password;
				if (password == "1") {
					break;
				}
			}if (to_string(hash<string>{}(password)) == client->get_password()) {
				system("cls");
				cout << "Enter your new password: ";
				cin >> password;
				client->set_password(password);
			}
		}
		else if (ch == '6') {
			is_true = false;
		}
		ch = '0';
	}
	system("cls");
	user_interfase(client);
}

void log_client() {
	string phoneNumber;
	cout << "Enter phone number: ";
	cin >> phoneNumber;

	Client *fi = UserBase::findUser(phoneNumber);
	if (fi != nullptr) {
		string pasword;
		cout << "Enter pasword: ";
		cin >> pasword;
		if (fi->get_password() != to_string(hash<string>{}(pasword))) {
			system("cls");
			cout << "Wrong password";
			Sleep(1000);
			system("cls");
			base_interfase();
		}
		else {
			user_interfase(fi);
		}
	}
	else {
		system("cls");
		cout << "Account not found";
		Sleep(1000);
		system("cls");
		base_interfase();
	}
}

void admin() {
							//Admin1234
	const string password = "11425957573334840840";
	string cin_password;
	while (password != to_string(hash<string>{}(cin_password))) {
		cout << "Enter password: ";
		cin >> cin_password;
		system("cls");
	}
	bool is_true = true;
	while (is_true) {
		char ch = '0';
		while (strchr("12345", ch) == nullptr) {
			cout << "1 - Show clients\n2 - Show cards\n3 - Block card\n4 - Unlock card\n5 - Exit\n";
			cin >> ch;
		}
		if (ch == '1') {
			system("cls");
			UserBase::print_base();
		}
		else if (ch == '2') {
			system("cls");
			CardBase::print_base();
		}
		else if (ch == '3') {
			system("cls");
			UserBase::print_base();
			cout << "Enter phone number user: ";
			string phoneNumber;
			cin >> phoneNumber;
			cout << "Enter id card: ";
			int idcard;
			cin >> idcard;
			Client *fi = UserBase::findUser(phoneNumber);
			if (fi != nullptr) {
				Card* cFi = &fi->returnCard(idcard);
				if (cFi != nullptr) {
					cFi->isnactive();
					system("cls");
				}
				else {
					system("cls");
					cout << "Card is not found";
					Sleep(1000);
					system("cls");
				}
			}
			else {
				system("cls");
				cout << "User is not found";
				Sleep(1000);
				system("cls");
			}
		}
		else if (ch == '4') {
			system("cls");
			UserBase::print_base();
			cout << "Enter phone number user: ";
			string phoneNumber;
			cin >> phoneNumber;
			cout << "Enter id card: ";
			int idcard;
			cin >> idcard;
			Client* fi = UserBase::findUser(phoneNumber);
			if (fi != nullptr) {
				Card* cFi = &fi->returnCard(idcard);
				if (cFi != nullptr) {
					cFi->active();
					system("cls");
				}
				else {
					system("cls");
					cout << "Card is not found";
					Sleep(1000);
					system("cls");
				}
			}
			else {
				system("cls");
				cout << "User is not found";
				Sleep(1000);
				system("cls");
			}
		}
		else if (ch == '5') {
			system("cls");
			is_true = false;
		}
	}
	base_interfase();
}

int base_interfase() {

	char ch = '0';
	while (strchr("1234", ch) == nullptr) {
		cout << "1 - Ñreate a new account\n2 - Log in to admin interface\n3 - Log in to your account\n4 - Exit\n";
		cin >> ch;
		system("cls");
	}
	if (ch == '1') {
		system("cls");
		createUser();
	}
	else if (ch == '2') {
		system("cls");
		admin();
	}
	else if (ch == '3') {
		system("cls");
		log_client();
	}
	else if (ch == '4') {
		return 1;
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	const string file_name = "base.bin";

	ifstream is;
	is.open(file_name);
	if (!is.is_open()) {
		cout << "File not find\nFile name - base.bin";
		cin.get();
	}
	else {
		UserBase::deserialization(is);
		is.close();
		base_interfase();

		ofstream os;
		os.open(file_name);
		if (!os.is_open()) {
			cout << "File not find\nFile name - base.bin";
			cin.get();
		}
		else {
			UserBase::serialization(os);
			return 0;
			cin.get();
		}
		cin.get();
	}
	cin.get();
}