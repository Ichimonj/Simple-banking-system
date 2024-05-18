#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
struct CardNumber
{
private:
    static int countCard;
    //4905 6111 1111 1119

    unsigned int  paymentSystem   = 4;      
    unsigned int  bankIdentifier  = 90561;
    unsigned long cardIdentifier  = 111111111;
    unsigned int  checkDigit      = 9;

public:
    CardNumber();
    CardNumber(string cardNumber);
    const CardNumber(const CardNumber& ex);
    
    const unsigned long recardIdentifier() const { return cardIdentifier; }

    void setCardNumber();
public:
    string encrypt(string kay);
    string decrypt(string cardNumber,string kay);
public:
    void serialization  (ofstream& FILE)const;
    void deserialization(ifstream& FILE);
public:
    const bool operator < (const CardNumber&u)const;
    friend ostream& operator<<(ostream& os, const CardNumber& ex);
};

