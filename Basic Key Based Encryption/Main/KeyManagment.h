#pragma once
#include <iostream>
#include <fstream>
#include <random>
#define KEY_FILENAME "key.bin"
using std::ofstream;
using std::ifstream;

struct KeyData
{
	int shift;
	char key[32];
};

class KeyManagment {
private:
	ifstream key_file_input;
	ofstream key_file_output;
protected:
	KeyData* _key = new KeyData;
public:
	void ReadKey();
	void SaveKey();
	void GenerateKey();
};