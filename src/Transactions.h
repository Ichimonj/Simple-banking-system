#pragma once
#include"Card.h"
#include<Windows.h>

namespace Transactions
{
	void translation(Card& sender, Card& recipient,int dollar,int cent);
	void replenish	(Card& recipient, int dollar, int cent);
	void withdrawal	(Card& sender, int dollar, int cent);
};

