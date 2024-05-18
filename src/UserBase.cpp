#include "UserBase.h"

namespace std {
	template <>
	struct hash<Client> {
		size_t operator()(const Client& client) const {
			return hash<string>()(client.returnPhone());
		}
	};
}
std::unordered_map<std::string, Client> userBase;

void UserBase::addClient(Client ex)
{
	userBase[ex.returnPhone()] = ex;
}
Client* UserBase::findUser(const string& phoneNumber)
{
    auto it = userBase.find(phoneNumber);
    if (it != userBase.end()) {
        return &(it->second); // Return pointer to client if found
    }
    else {
        return nullptr; // Return nullptr if not found
    }
}

void UserBase::serialization(ofstream& FILE)
{
	int userBaseSize = userBase.size();
	FILE.write((const char*)&userBaseSize, sizeof(int));
	for (auto& ex : userBase) {
		ex.second.serialization(FILE);
	}
}

void UserBase::deserialization(ifstream& FILE)
{
	int userBaseSize;
	FILE.read((char*)&userBaseSize, sizeof(int));
	for (int i = 0; i < userBaseSize; ++i) { 
		Client temp;
		temp.deserialization(FILE);
		userBase[temp.returnPhone()] = temp;
	}
	for (auto& ex : userBase) {
		ex.second.card_base_init();
	}
}

void UserBase::print_base()
{
	for (auto& ex : userBase) {
		cout << ex.second << endl;
	}
}

void UserBase::clearBase()
{
	userBase.clear();
}
