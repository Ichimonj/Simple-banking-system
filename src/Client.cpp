#include "Client.h"
int Client::countUser = 9;

Client::Client()
{
	cards.reserve(10);
}

Client::Client(string name, string surname, string patromymic,string phoneNumber,string pasword, Date berth)
{
	this->name		  = name;
	this->surname	  = surname;
	this->patronymic  = patromymic;
	this->berth		  = berth;
	this->phoneNumber = phoneNumber;
	this->password	  = to_string(hash<string>{}(pasword));
	id = countUser++;
	cards.reserve(10);

}

void Client::set_name(string name)
{
	this->name = name;
}

void Client::set_surname(string surname)
{
	this->surname = surname;
}

void Client::set_patronymic(string patronymic)
{
	this->patronymic = patronymic;
}

void Client::set_password(string pasword)
{
	this->password = to_string(hash<string>{}(pasword));
}


void Client::set_berth()
{
	this->berth = createDate(0, 0, 0);
}

void Client::createNewCard()
{
	if (cards.size() == 10) {
		return void();
	}
	else {
		cards.push_back(Card());
		cards[cards.size() - 1].setCardNumber();
		CardBase::add_card(&cards[cards.size() - 1]);
	}
}

void Client::deleteCard(int id)
{
	cards[id - 1].isnactive();
}

Card &Client::returnCard(int id) { return cards[id - 1]; }

string Client::returnPhone()const 
{
	return phoneNumber;
}

void Client::serialization(ofstream& FILE)
{
	int cardsSize = cards.size();
	FILE.write((const char*)&cardsSize, sizeof(int));

	for (auto& ex : cards) {
		ex.serialization(FILE);
	}
	FILE.write((const char*)&id, sizeof(int));
	
	int nameSize = name.size();
	FILE.write((const char*)&nameSize, sizeof(int));
	FILE.write(name.c_str(), nameSize);

	int surnameSize = surname.size();
	FILE.write((const char*)&surnameSize, sizeof(int));
	FILE.write(surname.c_str(), surnameSize);

	int patronymicSize = patronymic.size();
	FILE.write((const char*)&patronymicSize, sizeof(int));
	FILE.write(patronymic.c_str(), patronymicSize);

	int numberSize = phoneNumber.size();
	FILE.write((const char*)&numberSize, sizeof(int));
	FILE.write(phoneNumber.c_str(), numberSize);

	int paswordSize = password.size();
	FILE.write((const char*)&paswordSize, sizeof(int));
	FILE.write(password.c_str(), paswordSize);

	berth.serialization(FILE);

}

void Client::card_base_init()
{
	for (auto& ex : cards) {
		CardBase::add_card(&ex);
	}
}
void Client::deserialization(ifstream& FILE)
{
	int cardsSize;
	FILE.read((char*)&cardsSize, sizeof(int));

	cards.resize(cardsSize);
	CardBase::clear_base();

	for (int i = 0; i < cardsSize;i++) {
		Card ex;
		ex.deserialization(FILE);
		cards[i] = ex;
	}

	FILE.read((char*)&id, sizeof(int));


	int nameSize;
	FILE.read((char*)&nameSize, sizeof(int));
	char *nameBuffer = new char[nameSize];
	FILE.read(nameBuffer, nameSize);
	
	name = string(nameBuffer, nameSize);

	int surnameSize;
	FILE.read((char*)&surnameSize, sizeof(int));
	char *surnameBuffer = new char[surnameSize];
	FILE.read(surnameBuffer, surnameSize);

	surname = string(surnameBuffer, surnameSize);

	int patronymicSize;
	FILE.read((char*)&patronymicSize, sizeof(int));
	char *patronymicBuffer = new char[patronymicSize];
	FILE.read(patronymicBuffer, patronymicSize);

	patronymic = string(patronymicBuffer, patronymicSize);

	int phoneSize;
	FILE.read((char*)&phoneSize, sizeof(int));
	char* phonenumberBufer = new char[phoneSize];
	FILE.read(phonenumberBufer, phoneSize);

	phoneNumber = string(phonenumberBufer, phoneSize);

	int paswordSize;
	FILE.read((char*)&paswordSize, sizeof(int));
	char* paswordBufer = new char[paswordSize];
	FILE.read(paswordBufer, paswordSize);

	password = string(paswordBufer, paswordSize);

	berth.deserialization(FILE);

	delete[]nameBuffer;
	delete[]surnameBuffer;
	delete[]patronymicBuffer;
	delete[]phonenumberBufer;
	delete[]paswordBufer;
}

bool Client::operator<(const Client& ex) const
{
	return id < ex.id;
}


ostream& operator<<(ostream& os, const Client& ex)
{
	os << "Name - " << ex.name << "\nSurname - " << ex.surname << "\nPatronymic -   " << ex.patronymic
		<<"\nNumber - "<<ex.phoneNumber;
	os << "\nDate berth - " << ex.berth;
	os << "\nCards:";
	for (auto& ex : ex.cards) {
		os << "\n__________\n";
		os << ex << endl;
		os << "__________\n";
	}
	return os;
}
