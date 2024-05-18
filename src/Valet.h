#pragma once
#include<iostream>
#include<fstream>

using namespace std;
class Valet
{
private:
	int dollar;
	int cent;
public:
	Valet();
	Valet(int dollar, int cent);
	const Valet(const Valet& ex);

	Valet& checkValet();

	Valet& operator +=(const Valet& ex);
	Valet& operator -=(const Valet& ex);
	
	Valet& operator -(const Valet& ex);
	Valet& operator +(const Valet& ex);

	bool operator < (const Valet& ex);
	bool operator <=(const Valet& ex);
public:
	void serialization	(ofstream& FILE)const;
	void deserialization(ifstream& FILE);

public:
	friend ostream& operator<<(ostream& os, const Valet& ex);
};