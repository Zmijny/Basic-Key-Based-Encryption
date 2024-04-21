#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "KeyManagment.h"
#define NUMBERS_AS_TEXT_ERROR 48
#define MULTIPLIER 6

#define EE_DEBUG 0

class Encryption : KeyManagment
{
	ifstream input;
	ofstream output;
public:
	enum {
		Plain_Text = 0,
		File
	};
	void Encrypt(std::string data, int type);
	void Decrypt(std::string data, int type);
};
