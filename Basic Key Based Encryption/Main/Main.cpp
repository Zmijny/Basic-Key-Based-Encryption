#include "Main.h"
#define EE_DEBUG 1

void Main::Encrypt(std::string text)
{
	std::vector<int> text_encrypted;
	ReadKey();
	
	int j = 0;
	for (int i = 0; i <= text.length();i++)
	{
		text_encrypted.push_back((static_cast<int>(text[i]) + ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) + 100);
		int a = static_cast<int>(_key->key[j]);
		int b = _key->shift;
		int c = (static_cast<int>(_key->key[j]) - _key->shift) / 2;
		if (j != 31)
			j++;
		else
			j = 0;
	}

	output.open("output_file.txt");
	for (int i = 0; i < text_encrypted.size(); i++)
	{
		output << text_encrypted[i];
	}
	output.close();
	//Debug
#if EE_DEBUG == 1
	printf("\n\n\nNormal text: %s", text.c_str());
	std::cout << "\nEncrypted text: ";
	for (auto n : text_encrypted)
	{
		printf("%d ", n);
	}
#endif
}

void Main::Decrypt(std::string text)
{
	int character[3];
	std::vector<char> text_decrypted;
	ReadKey();
	/*
	std::string tst;
	input.open("output_file.txt");
	while(std::getline(input, tst)){}
	input.close();
	*/
	int j = 0;
	int k = 0;
	for (int i = 0; i <= (text.length() / 3); i++)
	{
		character[k] = (static_cast<int>(text[i]) - 100 - ((static_cast<int>(_key->key[j]) - _key->shift) / 2) );
		if (j != 31)
			j++;
		else
			j = 0;

		if (k < 2)
			k++;
		else
		{
			text_decrypted.push_back(static_cast<char>((character[0] * 100) + (character[1] * 10) + character[2]));
			k = 0;
		}
			
	}

	/*
	output.open("output_file.txt");
	for(int i = 0; i <= text_decrypted.size(); i++)
	{
		output << text_decrypted[i];
	}
	output.close();
	*/
	//Debug
#if EE_DEBUG == 1
	printf("\n\nEncrypted text: %s", text.c_str());
	printf("\nDecrypted text: ");
	for (auto n : text_decrypted)
	{
		printf("%s ", n);
	}
#endif
}


// Main
int main(int* argc, char* argv[])
{
	Main _main;
	KeyManagment k3y;
	//std::string file_opened = argv[1];

	//k3y.GenerateKey();
	//k3y.SaveKey();

	std::string test_text = "Hello World";

	_main.Decrypt(test_text);
}