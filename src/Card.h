#pragma once
#include"cardNumber.h"
#include"Date.h"
#include"Valet.h"
#include<ctime>

struct Card
{
private:
	bool activity = true;
	CardNumber cardNumber;
	Date  dateClosing = Date(2030,12,10);
	Valet money = Valet();
	int   cvv;
public:
	Card();
	Card(Valet& ex);
	const Card(const Card& ex);

	Date getDate() { return dateClosing; }
	int  getCvv() { return cvv; }

	bool is_active();
	bool isnactive();
	bool active();

	Card& operator-=(Valet& ex);
	Card& operator+=(Valet& ex);

	Valet& returnMoney();
	unsigned long recardIdentifier() const { return cardNumber.recardIdentifier(); }

	void setCardNumber();

public:
	void serialization	(ofstream& FILE)const;
	void deserialization(ifstream& FILE);

public:
	const bool operator < (const Card& ex) const;
	friend ostream& operator<<(ostream& os, const Card& ex);
};
