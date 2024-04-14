#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "KeyManagment.h"

class Main : KeyManagment
{
	ifstream input;
	ofstream output;
public:
	void Encrypt(std::string text);
	void Decrypt(std::string text);
};
