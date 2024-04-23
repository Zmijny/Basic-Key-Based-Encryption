#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
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
	void ReadKey(char* path);
	void SaveKey(char* path);
	void GenerateKey();
};