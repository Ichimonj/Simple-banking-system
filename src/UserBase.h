#pragma once
#include"Client.h"
#include<set>

namespace UserBase
{
	void addClient(Client ex);
	Client* findUser(const string& phoneNumber);
	void serialization   (ofstream& FILE);
	void deserialization(ifstream& FILE);
	
	void print_base();
	void clearBase();

};

