#include "Date.h"

Date::Date(int year, int month, int day)
{
	this->year  = year;
	this->month = month;
	this->day   = day;
}

void Date::serialization(ofstream& FILE) const
{
	FILE.write((const char*)&year,  sizeof(int));
	FILE.write((const char*)&month, sizeof(int));
	FILE.write((const char*)&day,   sizeof(int));
}

void Date::deserialization(ifstream& FILE)
{
	FILE.read((char*)&year,  sizeof(int));
	FILE.read((char*)&month, sizeof(int));
	FILE.read((char*)&day,   sizeof(int));
}

bool Date::operator==(const Date& ex)
{
	if (year == ex.year && month == ex.month && day == ex.day)
		return true;
	return false;
}

ostream& operator<<(ostream& os, const Date& ex)
{
	os << ex.year << ',' << ex.month << ',' << ex.day;
	return os;
}

Date createDate(int year, int day, int month)
{
	while (year < 1900 || year>2024) {
		cout << "Plese enter true year: ";
		cin >> year;
	}
	while (month <= 0 || month > 13) {
		cout << "Plese enter true month: ";
		cin >> month;
	}

	int maxDay;

	switch (month)
	{
	case 1:maxDay  = 31; break;
	case 2:maxDay  = 28; break;
	case 3:maxDay  = 31; break;
	case 4:maxDay  = 30; break;
	case 5:maxDay  = 31; break;
	case 6:maxDay  = 30; break;
	case 7:maxDay  = 31; break;
	case 8:maxDay  = 31; break;
	case 9:maxDay  = 30; break;
	case 10:maxDay = 31; break;
	case 11:maxDay = 30; break;
	case 12:maxDay = 31; break;
	default:0;
	}

	while (day <= 0 || day > maxDay) {
		cout << "Plese enter true day: ";
		cin >> day;
	}
	return Date(year, month, day);
}