#include "CardBase.h"
unordered_map<unsigned long, Card*> cardBase;

void CardBase::add_card(Card* ex)
{
	cardBase.insert(make_pair(ex->recardIdentifier(), ex));
}

Card *CardBase::find_card(string cardNumber)
{
	if (cardNumber.size() == 16) {
		unsigned long cardIdentifier = stoi(cardNumber.substr(6, 9));
		auto fi = cardBase.find(cardIdentifier);
		if (&fi != nullptr) {
			return fi->second;
		}
	}
	cout << "Card not found or card number is incorrect" << endl;
	return nullptr;
}

void CardBase::print_base()
{
	for (auto& ex : cardBase) {
		cout << *ex.second << endl;
	}
}

void CardBase::clear_base()
{
	cardBase.clear();
}
	