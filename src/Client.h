#pragma once
#include"Card.h"
#include"vector"
#include"Date.h"
#include"CardBase.h"

class Client
{
private:
	vector<Card>cards;

	static int countUser;
	int    id		  = 0;
	string name		  = "unname";
	string surname	  = "unname";
	string patronymic = "unname";

	string password    = "1234";
	string phoneNumber = "00000000000";
	Date   berth	  = Date(2003,12,12);
public:
	Client();
	Client(string name, string surname, string patromymic, string phoneNumber,string pasword, Date berth);
public:
	void set_name(string name);
	void set_surname(string surname);
	void set_patronymic(string patronymic);
	void set_password(string pasword);
	void set_berth();
	
	string get_password() {return password;}
	int get_size_cards() { return cards.size(); }
public:
	void createNewCard();
	void deleteCard(int id);

	int returdCardsSize() { return cards.size(); }
	Card& returnCard(int id);
	string returnPhone()const;

public:
	void serialization(ofstream& FILE);
	void card_base_init();
	void deserialization(ifstream& FILE);

	bool operator <(const Client& ex)const;
	friend ostream& operator<<(ostream& os, const Client& ex);
};

