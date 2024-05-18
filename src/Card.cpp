#include "Card.h"
Card::Card() {
	srand(time(NULL));
	cvv = rand() % 900+100;
}

Card::Card(Valet& ex)
{
	money = ex;
	cvv = rand() % 900 + 100;
}

Card::Card(const Card& ex)
{
	activity    = ex.activity;
	cardNumber  = ex.cardNumber;
	dateClosing = ex.dateClosing;
	money       = ex.money;
	cvv         = ex.cvv;

}

bool Card::is_active()
{
	return activity;
}

bool Card::isnactive()
{
	activity = false;
	return activity;
}

bool Card::active()
{
	activity = true;
	return activity;
}


Card& Card::operator-=(Valet& ex)
{
	money -= ex;
	return *this;
}

Card& Card::operator+=(Valet& ex)
{
	money += ex;
	return *this;
}

Valet& Card::returnMoney()
{
	return money;
}

void Card::setCardNumber()
{
	cardNumber.setCardNumber();
}

void Card::serialization(ofstream& FILE) const
{
	FILE.write((const char*)&activity, sizeof(bool));
	cardNumber. serialization(FILE);
	dateClosing.serialization(FILE);
	money.		serialization(FILE);
	FILE.write((const char*)&cvv, sizeof(int));
}

void Card::deserialization(ifstream& FILE)
{
	FILE.read((char*)&activity, sizeof(bool));
	cardNumber.	deserialization(FILE);
	dateClosing.deserialization(FILE);
	money.		deserialization(FILE);
	FILE.read((char*)&cvv, sizeof(int));
}


const bool Card::operator<(const Card& ex) const
{
	return cardNumber < ex.cardNumber;
}

ostream& operator<<(ostream& os, const Card& ex)
{
	if (ex.activity) {
		os << "Card active\n";

	}
	else {
		os << "Card not active\n";
	}
	os	<< "Card Number: " << ex.cardNumber
		<< "\nDate closing card: " << ex.dateClosing
		<< "\nMoney\n" << ex.money
		<< "\ncvv:\t" << ex.cvv;
	return os;
}


