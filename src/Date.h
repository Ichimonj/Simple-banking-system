#pragma once
#include<iostream>
#include<fstream>

using namespace std;
struct Date
{
private:
	int year;
	int month;
	int day;
public:
	Date() = default;
	Date(int year, int month, int day);

public:
	void serialization	(ofstream& FILE)const;
	void deserialization(ifstream& FILE);

public:
	bool operator==(const Date& ex);
	friend ostream& operator<<(ostream& os, const Date& ex);
};

Date createDate(int year, int month, int day);
