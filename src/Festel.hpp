#pragma once

#include<iostream>
#include<vector>
#include<bitset>
#include<array>
#include<algorithm>

//festel cipher
//шифр фестеля

/*
int main() {
	string msg = "dead reckoning";
	string kay = "idea";

	string coding   = Festel::to_encrypt(msg, kay);
	cout << coding << endl;   //└♥5√RG╔▄м*T▬mj♦╦

	string decoding = Festel::to_decipher(coding, kay);
	cout << decoding << endl; //dead reckoning
}
*/

using namespace std;

namespace Festel {

	int binaryToDecimal(vector<bool>bitMsg) {
		int decimal = 0;
		int power = 0;
		for (int i = bitMsg.size() - 1; i >= 0; i--) {
			if (bitMsg[i]) {
				decimal += pow(2, power);
			}
			power++;
		}
		return decimal;
	}

	vector<bool> decimalToBinary(int decimalNumber) {
		vector<bool> ret;

		while (decimalNumber > 0) {
			ret.insert(ret.begin(), decimalNumber % 2);
			decimalNumber /= 2;
		}
		while (true)
		{
			if (ret.size() < 4) {
				ret.insert(ret.begin(), 0);
			}
			else
			{
				break;
			}
		}
		return ret;
	}

	vector<bool>retmsg_64(string msg) {
		vector<bool>ret;
		if (msg.size() > 8) {
			for (int i = 0; i < 8; i++) {
				for (int j = 7; j >= 0; j--) {
					ret.push_back((msg[i] >> j) & 1);
				}
			}
			return ret;
		}
		for (;;) {
			if (msg.size() * 8 + ret.size() != 64) {
				for (int i = 0; i < 8; i++) {
					ret.push_back(0);
				}
			}
			else {
				break;
			}
		}
		for (int i = 0; i < msg.size(); i++) {
			for (int j = 7; j >= 0; j--) {
				ret.push_back((msg[i] >> j) & 1);
			}
		}
		return ret;
	}


	array<int, 64>table1{
		58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
	};

	array<int, 48>table2{
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1
	};

	array<int, 64>table3{
		40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
	};

	array<array<int, 16>, 32>sTables{
	{
		{9,4,7,15,13,8,14,2,6,0,10,1,5,3,12},
		{15,13,4,2,5,10,3,0,1,11,12,6,8,7,14},
		{2,9,12,13,0,3,6,14,4,11,8,15,10,7,5},
		{9,2,13,11,1,3,4,5,8,0,14,6,15,10,7},

		{12,14,5,11,0,2,9,1,15,7,8,6,10,13,3},
		{3,7,5,9,1,13,12,4,8,6,10,15,11,2,14},
		{6,3,13,9,12,4,5,0,8,2,10,14,15,11,1},
		{12,14,7,1,2,6,0,5,13,10,15,8,11,4,3},

		{0,9,6,11,8,14,7,15,1,3,5,2,10,13,12},
		{6,1,5,15,8,14,9,7,3,2,11,13,4,0,12},
		{10,14,4,11,13,8,9,5,1,6,0,2,7,15,3},
		{0,7,15,3,10,9,13,5,14,6,1,8,2,12,11},

		{3,7,2,11,1,13,9,6,10,14,4,15,12,5,8},
		{10,12,7,1,0,14,2,5,15,8,6,3,13,11,4},
		{0,5,8,12,3,14,11,2,13,10,7,4,1,6,9},
		{4,1,0,15,2,11,14,8,12,7,10,5,9,13,3},

		{10,0,14,5,12,6,1,8,2,15,4,9,7,11,13},
		{13,6,8,15,7,5,1,9,2,3,12,10,0,11,4},
		{4,15,9,11,5,6,2,0,10,14,8,12,13,3,1},
		{7,12,1,11,15,14,3,8,6,9,10,0,5,13,2},

		{14,4,1,9,8,15,7,0,11,6,5,12,13,10,2},
		{1,9,15,7,5,0,11,10,8,6,13,14,2,3,12},
		{8,10,7,4,12,6,3,2,15,9,13,0,5,11,1},
		{11,6,2,7,15,3,1,14,10,8,9,12,13,4,0},

		{1,15,2,5,4,9,11,7,6,0,13,10,8,3,14},
		{5,11,10,14,7,9,3,2,15,4,8,1,6,0,13},
		{11,4,3,5,15,1,10,9,6,13,7,14,8,0,12},
		{14,0,3,11,12,8,7,6,10,9,1,4,2,5,13},

		{5,9,3,1,4,13,2,0,15,11,7,12,10,14,6},
		{8,6,11,1,14,0,13,2,15,12,7,9,10,5,3},
		{15,14,12,3,13,1,7,4,2,11,6,8,5,0,9},
		{2,11,4,14,6,0,1,3,15,13,12,5,10,9,8},
	}
	};

	array<int, 56>kayTable1{
		57,49,41,33,25,17,9,1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,21,13,5,28,20,12,4
	};

	array<int, 16>kayTable2{
		1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
	};

	array<int, 48>kayTable3{
		14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,
		26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,
		51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
	};

	//encryption
	vector<bool>festel_coding(vector<bool>msg_, vector<bool>kay_) {
		//create 16 keys
		vector<bool>kay(56);
		for (int i = 0; i < 56; i++) {
			kay[i] = kay_[kayTable1[i] - 1];
		}

		//split the key in half
		vector<bool>kay1(kay.begin(), kay.begin() + 28);
		vector<bool>kay2(kay.begin() + 28, kay.end());

		//kays
		vector<vector<bool>>kayArray(16, vector<bool>(48));

		for (int i = 0; i < 16; i++) {
			//move the two halves of the key
			rotate(kay1.begin(), kay1.begin() + kayTable2[i], kay1.end());
			rotate(kay2.begin(), kay2.begin() + kayTable2[i], kay2.end());

			//conclude them
			vector<bool>kay_56 = kay1;
			kay_56.insert(kay_56.end(), kay2.begin(), kay2.end());
			//permutation
			vector<bool>kay_48(48);
			for (int i = 0; i < 48; i++) {
				kay_48[i] = kay_56[kayTable3[i] - 1];
			}
			//adding keys to the array
			kayArray[i].clear();
			kayArray[i].insert(kayArray[i].begin(), kay_48.begin(), kay_48.end());

			kay_56.clear();
			kay_48.clear();
		}


		//cipher
		//primary permutation
		vector<bool>msg(64);
		for (int i = 0; i < 64; i++) {
			msg[i] = msg_[table1[i] - 1];
		}
		vector<bool>l0(msg.begin(), msg.begin() + 32);
		vector<bool>r0(msg.begin() + 32, msg.end());
		vector<bool>r048(48);

		//16 rounds
		for (int round = 0; round < 16; round++) {
			for (int i = 0; i < 48; i++) {
				r048[i] = r0[table2[i] - 1];
				r048[i] = r048[i] ^ kayArray[round][i];
			}

			vector<bool>permutRet(32);
			permutRet.clear();
			int column = 0;
			int tableNumber = 0;

			for (int i = 0; i < 8; i++) {
				vector<bool>sTableIndx(r048.begin(), r048.begin() + 6);
				vector<bool>retbDTB(decimalToBinary(sTables
					[binaryToDecimal({ sTableIndx.front(),sTableIndx.back() }) + tableNumber]
					[binaryToDecimal({ sTableIndx.begin() + 1,sTableIndx.end() - 1 })]
				));
				permutRet.insert(permutRet.end(), retbDTB.begin(), retbDTB.end());
				column += 6;
				tableNumber += 4;
			}
			vector<bool>r1(32);
			for (int i = 0; i < 32; i++) {
				r1[i] = l0[i] ^ permutRet[i];
			}
			l0 = r0;
			r0 = r1;
		}
		vector<bool>beforeFinish(r0);
		beforeFinish.insert(beforeFinish.end(), l0.begin(), l0.end());
		vector<bool>ret(64);

		for (int i = 0; i < 64; i++) {
			ret[i] = beforeFinish[table3[i] - 1];
		}
		return ret;

	}
	//decryption
	vector<bool>festel_decoding(vector<bool>msg_, vector<bool>kay_) {
		//create 16 keys
		vector<bool>kay(56);
		for (int i = 0; i < 56; i++) {
			kay[i] = kay_[kayTable1[i] - 1];
		}

		//split the key in half
		vector<bool>kay1(kay.begin(), kay.begin() + 28);
		vector<bool>kay2(kay.begin() + 28, kay.end());

		//kays
		vector<vector<bool>>kayArray(16, vector<bool>(48));

		for (int i = 0; i < 16; i++) {
			//move the two halves of the key
			rotate(kay1.begin(), kay1.begin() + kayTable2[i], kay1.end());
			rotate(kay2.begin(), kay2.begin() + kayTable2[i], kay2.end());

			//conclude them
			vector<bool>kay_56 = kay1;
			kay_56.insert(kay_56.end(), kay2.begin(), kay2.end());
			//permutation
			vector<bool>kay_48(48);
			for (int i = 0; i < 48; i++) {
				kay_48[i] = kay_56[kayTable3[i] - 1];
			}
			//adding keys to the array
			kayArray[i].clear();
			kayArray[i].insert(kayArray[i].begin(), kay_48.begin(), kay_48.end());

			kay_56.clear();
			kay_48.clear();
		}


		//cipher
		//primary permutation
		vector<bool>msg(64);
		for (int i = 0; i < 64; i++) {
			msg[i] = msg_[table1[i] - 1];
		}
		vector<bool>l0(msg.begin(), msg.begin() + 32);
		vector<bool>r0(msg.begin() + 32, msg.end());
		vector<bool>r048(48);

		//16 rounds
		for (int round = 15; round >= 0; round--) {
			for (int i = 0; i < 48; i++) {
				r048[i] = r0[table2[i] - 1];
				r048[i] = r048[i] ^ kayArray[round][i];
			}

			vector<bool>permutRet(32);
			permutRet.clear();
			int column = 0;
			int tableNumber = 0;

			for (int i = 0; i < 8; i++) {
				vector<bool>sTableIndx(r048.begin(), r048.begin() + 6);
				vector<bool>retbDTB(decimalToBinary(sTables
					[binaryToDecimal({ sTableIndx.front(),sTableIndx.back() }) + tableNumber]
					[binaryToDecimal({ sTableIndx.begin() + 1,sTableIndx.end() - 1 })]
				));
				permutRet.insert(permutRet.end(), retbDTB.begin(), retbDTB.end());
				column += 6;
				tableNumber += 4;
			}
			vector<bool>r1(32);
			for (int i = 0; i < 32; i++) {
				r1[i] = l0[i] ^ permutRet[i];
			}
			l0 = r0;
			r0 = r1;
		}
		vector<bool>beforeFinish(r0);
		beforeFinish.insert(beforeFinish.end(), l0.begin(), l0.end());
		vector<bool>ret(64);

		for (int i = 0; i < 64; i++) {
			ret[i] = beforeFinish[table3[i] - 1];
		}
		return ret;

	}

	string to_encrypt(string msg, string kay) {
		vector<string>msg_array;
		if (msg.size() <= 8) {
			msg_array.push_back(msg);
		}
		else {

			for (int i = 0; i < msg.size(); i += 8) {
				if (i + 8 > msg.size()) {
					msg_array.push_back(string(msg, i, msg.size() - i));
				}
				else {
					msg_array.push_back(string(msg, i, 8));
				}
			}
		}

		string encrypt_msg;
		for (string& ex : msg_array) {
			vector<bool> binMsg = festel_coding(Festel::retmsg_64(ex), retmsg_64(kay));
			for (int i = 0; i < 64; i += 8) {
				bitset<8>simbol;
				for (int j = 0; j < 8; j++) {
					simbol[7 - j] = binMsg[i + j];
				}
				encrypt_msg.push_back(static_cast<char>(simbol.to_ulong()));
			}
		}

		return encrypt_msg;
	}

	string to_decipher(string msg, string kay) {
		vector<string>msg_array;
		if (msg.size() <= 8) {
			msg_array.push_back(msg);
		}
		else {

			for (int i = 0; i < msg.size(); i += 8) {
				if (i + 8 > msg.size()) {
					msg_array.push_back(string(msg, i, msg.size() - i));
				}
				else {
					msg_array.push_back(string(msg, i, 8));
				}
			}
		}

		string decipher_msg;
		for (string& ex : msg_array) {
			vector<bool> binMsg = festel_decoding(retmsg_64(ex), retmsg_64(kay));
			for (int i = 0; i < 64; i += 8) {
				bitset<8>simbol;
				for (int j = 0; j < 8; j++) {
					simbol[7 - j] = binMsg[i + j];
				}
				decipher_msg.push_back(static_cast<char>(simbol.to_ulong()));
			}
		}

		return decipher_msg;
	}
}