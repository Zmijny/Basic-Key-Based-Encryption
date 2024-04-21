#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "KeyManagment.h"
#define NUMBERS_AS_TEXT_ERROR 48
#define MULTIPLIER 6

class Main : KeyManagment
{
	ifstream input;
	ofstream output;
public:
	void Encrypt(std::string text);
	void Decrypt(std::string text);
};
