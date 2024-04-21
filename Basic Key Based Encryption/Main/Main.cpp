#include "Main.h"
#define EE_DEBUG 1



void Main::Encrypt(std::string text)
{
	std::vector<int> text_encrypted;
	ReadKey();
	
	int j = 0;
	for (int i = 0; i <= text.length();i++)
	{
		text_encrypted.push_back((static_cast<int>(text[i]) + ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) + (static_cast<int>(_key->key[j]) * MULTIPLIER));

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
	std::string encrypted_text;
	ReadKey();
	input.open("output_file.txt");
	input >> encrypted_text;
	input.close();

	int j = 0;
	for (int i = 0; i < encrypted_text.length(); i++)
	{
		if (i == encrypted_text.length() - 1)
			break;

		character[0] = static_cast<int>(encrypted_text[i]) - NUMBERS_AS_TEXT_ERROR;
		character[1] = static_cast<int>(encrypted_text[i + 1]) - NUMBERS_AS_TEXT_ERROR;
		character[2] = static_cast<int>(encrypted_text[i + 2]) - NUMBERS_AS_TEXT_ERROR;
		i += 2;

		int dummy = character[0] * 100 + character[1] * 10 + character[2];

		text_decrypted.push_back(static_cast<char>(dummy - ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) - ((static_cast<int>(_key->key[j]) * MULTIPLIER)));

		if (j != 31)
			j++;
		else
			j = 0;
	}
	

	//Debug
#if EE_DEBUG == 1
	printf("\n\nEncrypted text: %s", encrypted_text.c_str());
	printf("\nDecrypted text: ");
	for (auto n : text_decrypted)
	{
		printf("%c", n);
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

	std::string test_text = "I'm sure that your're never gonna be able to read it!";

	_main.Decrypt(test_text);
}