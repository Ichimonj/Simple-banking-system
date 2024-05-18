#include "cardNumber.h"
#include"Festel.hpp"

int CardNumber::countCard = 0;

CardNumber::CardNumber()
{
}

CardNumber::CardNumber(string cardNumber)
{
    while (cardNumber.size() < 16) {
        cout << "Invalid card number format\nPlease enter another number: ";
        cin >> cardNumber;
    }
    paymentSystem  = stoi(cardNumber.substr(0,1));
    bankIdentifier = stoi(cardNumber.substr(1, 5));
    cardIdentifier = stoi(cardNumber.substr(6, 9));
    checkDigit     = stoi(cardNumber.substr(15, 1));
}

CardNumber::CardNumber(const CardNumber& ex)
{
    paymentSystem   = ex.paymentSystem;
    bankIdentifier  = ex.bankIdentifier;
    cardIdentifier  = ex.cardIdentifier;
    checkDigit      = ex.checkDigit;
}


void CardNumber::setCardNumber()
{
    cardIdentifier += countCard;
    countCard++;
}

string CardNumber::encrypt(const string kay)
{
    string _baseCardNumber = to_string(paymentSystem)+=to_string(bankIdentifier)+=to_string(cardIdentifier)+=to_string(checkDigit);
    _baseCardNumber = Festel::to_encrypt(_baseCardNumber, kay);

    return _baseCardNumber;
}

string CardNumber::decrypt(const string cardNumber,const string kay)
{
    string _baseCardNumber = Festel::to_decipher(cardNumber, kay);

    paymentSystem = stoi(_baseCardNumber.substr(0, 1));
    bankIdentifier = stoi(_baseCardNumber.substr(1, 5));
    cardIdentifier = stoi(_baseCardNumber.substr(6, 9));
    checkDigit = stoi(_baseCardNumber.substr(15, 1));

    return _baseCardNumber;
}

void CardNumber::serialization(ofstream& FILE) const
{
    const string kay = "IOsh";
    string _baseCardNumber = to_string(paymentSystem) += to_string(bankIdentifier) += to_string(cardIdentifier) += to_string(checkDigit);
    _baseCardNumber = Festel::to_encrypt(_baseCardNumber, kay);

    int sizeKay = kay.size();
    int sizeCardNumber = _baseCardNumber.size();

    FILE.write((const char*)&sizeKay, sizeof(int));
    FILE.write((const char*)&kay, sizeKay);

    FILE.write((const char*)&sizeCardNumber, sizeof(int));
    FILE.write((const char*)&_baseCardNumber, sizeCardNumber);
}

void CardNumber::deserialization(ifstream& FILE)
{
    int sizeKay;
    string kay;
    int sizeCard;
    string _baseCardNumber;

    FILE.read((char*)&sizeKay, sizeof(int));
    char* kayBufer = new char[sizeKay];
    FILE.read((char*)&kayBufer, sizeKay);
    kay = string(kayBufer, sizeKay);

    FILE.read((char*)&sizeCard, sizeof(int));
    char* cardBufer = new char[sizeCard];
    FILE.read((char*)&cardBufer, sizeCard);
    _baseCardNumber = string(cardBufer, sizeCard);

    _baseCardNumber = Festel::to_decipher(_baseCardNumber, kay);

    paymentSystem   = stoi(_baseCardNumber.substr(0, 1));
    bankIdentifier  = stoi(_baseCardNumber.substr(1, 5));
    cardIdentifier  = stoi(_baseCardNumber.substr(6, 9));
    checkDigit      = stoi(_baseCardNumber.substr(15, 1));       
}

const bool CardNumber::operator<(const CardNumber& u) const
{
    return cardIdentifier < u.cardIdentifier;
}

ostream& operator<<(ostream& os, const CardNumber& ex)
{
    string CardNumber = to_string(ex.paymentSystem);
    CardNumber+=(to_string(ex.bankIdentifier));
    CardNumber += (to_string(ex.cardIdentifier));
    CardNumber += (to_string(ex.checkDigit));

    CardNumber.insert(4, " ");
    CardNumber.insert(9, " ");
    CardNumber.insert(14, " ");

    os << CardNumber;
    return os;
}