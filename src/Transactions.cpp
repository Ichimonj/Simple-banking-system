#include "Transactions.h"

void Transactions::translation(Card& sender, Card& recipient, int dollar, int cent)
{
	Valet transf(dollar, cent);
	transf.checkValet();

	if (transf <= sender.returnMoney()) {
		sender -= transf;
		recipient += transf;
	}
	else {
		system("cls");
		cout << "Not enough money";
		Sleep(1000);
		system("cls");
	}
}

void Transactions::replenish(Card& recipient, int dollar, int cent)
{
	Valet transf(dollar, cent);
	transf.checkValet();
	recipient += transf;
}

void Transactions::withdrawal(Card& sender, int dollar, int cent)
{
	Valet transf(dollar, cent);
	transf.checkValet();
	if (transf <= sender.returnMoney()) {
		sender -= transf;
	}
	else {
		system("cls");
		cout << "Not enough money";
		Sleep(1000);
		system("cls");
	}
}
