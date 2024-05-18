#pragma once
#include"Card.h"
#include<unordered_map>

namespace CardBase
{
	void add_card(Card* ex);
	Card* find_card(string cardNumber);

	void print_base();
	void clear_base();
};

