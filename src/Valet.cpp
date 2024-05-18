#include "Valet.h"

Valet::Valet()
{
	dollar = 0;
	cent   = 0;
}

Valet::Valet(int dollar, int cent)
{
	this->dollar = dollar;
	this->cent   = cent;
}

Valet::Valet(const Valet& ex)
{
	this->dollar = ex.dollar;
	this->cent   = ex.cent;
}

Valet& Valet::checkValet()
{
	if (cent >= 100) {
		int amount = cent / 100;
		cent -= amount * 100;
		dollar += amount;
	}
	else if (cent < 0)
	{
		int amount = cent / 100;
		dollar += amount;
		cent += fabs(amount) * 100;

		if (cent < 0) {
			dollar -= 1;
			cent += 100;
		}
	}
	return *this;
}

Valet& Valet::operator+=(const Valet& ex)
{
	this->dollar += ex.dollar;
	this->cent	 += ex.cent;
	checkValet();
	return *this;
}

Valet& Valet::operator-=(const Valet& ex)
{
	this->dollar -= ex.dollar;
	this->cent   -= ex.cent;
	checkValet();
	return *this;
}

Valet& Valet::operator-(const Valet& ex)
{
	Valet r(dollar-ex.dollar,cent-ex.cent);
	r.checkValet();
	return r;
}

Valet& Valet::operator+(const Valet& ex)
{
	Valet r(dollar + ex.dollar, cent + ex.cent);
	r.checkValet();
	return r;
}

bool Valet::operator<(const Valet& ex)
{
	if (dollar < ex.dollar)
		return true;
	else if (dollar > ex.dollar)
		return false;
	else if (cent < ex.cent)
		return true;
	return false;
}

bool Valet::operator<=(const Valet& ex){

	if (dollar < ex.dollar)
		return true;
	else if (dollar > ex.dollar)
		return false;
	else if (cent < ex.cent)
		return true;
	if (dollar == ex.dollar && cent == ex.cent)
		return true;

	return false;
}

void Valet::serialization(ofstream& FILE) const
{
	FILE.write((const char*)&dollar, sizeof(int));
	FILE.write((const char*)&cent,   sizeof(int));
}

void Valet::deserialization(ifstream& FILE)
{
	FILE.read((char*)&dollar, sizeof(int));
	FILE.read((char*)&cent,   sizeof(int));
}


ostream& operator<<(ostream& os, const Valet& ex)
{
	os << "Dollar:\t" << ex.dollar << "\nCent:\t" << ex.cent;
	return os;
}
