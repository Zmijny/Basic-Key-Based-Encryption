#include <iostream>
#include <fstream>
#include <conio.h>
#include "Encryption.h"

void WaitForUserInput();

int main(int* argc, char* argv[])
{
	printf("Where the program was executed: %s", argv[0]);

	Encryption _encryption;
	KeyManagment encrytpion_key;
	//encrytpion_key.ReadKey(argv[0]);
	int user_input;

	if (argv[1] != nullptr)
	{
		
		printf("\nOpened File Path: %s", argv[1]);

		std::string file_opened = argv[1];
		std::fstream file_selected(file_opened);
		if (!file_selected.is_open())
		{
			printf("\nCouldn't open the desired file");
		}

		while (true)
		{
			printf("\nWhat do you want to do with the file?\nEncrypt - 1\nDecrypt - 2\nGenerate New Encryption Key - 3\nOption: ");
			std::cin >> user_input;
			switch (user_input)
			{
			case 1:
				_encryption.Encrypt(file_opened, _encryption.File, argv[0]);
				printf("File Encrypted");
				WaitForUserInput();
				return 0;
			case 2:
				_encryption.Decrypt(file_opened, _encryption.File, argv[0]);
				printf("File Decrypted");		
				WaitForUserInput();
				return 0;
			case 3:
				encrytpion_key.GenerateKey();
				encrytpion_key.SaveKey(argv[0]);
				printf("Generated and saved the new Encryption key");
				WaitForUserInput();
				break;
			default:
				printf("\nPlease choose a number from 1 to 3 to select your option");
				WaitForUserInput();
				system("cls");
				break;
			}
		}
		file_selected.close();
	}
	else
	{
		std::string input_string;
		
		printf("\nPlease input a string you wish to encrypt/decrypt\n");
		getline(std::cin, input_string);
		system("cls");

		while (true)
		{
			printf("\nEncrypt - 1\nDecrypt - 2\nGenerate New Encryption Key - 3\nOption: ");
			std::cin >> user_input;
			switch (user_input)
			{
			case 1:
				_encryption.Encrypt(input_string, _encryption.Plain_Text, argv[0]);
				printf("Text Encrypted");
				WaitForUserInput();
				return 0;
			case 2:
				_encryption.Decrypt(input_string, _encryption.Plain_Text, argv[0]);
				printf("Text Decrypted");
				WaitForUserInput();
				return 0;
			case 3:
				encrytpion_key.GenerateKey();
				encrytpion_key.SaveKey(argv[0]);
				printf("Generated and saved the new Encryption key");
				break;
			default:
				printf("\nPlease choose a number from 1 to 3 to select your option");
				WaitForUserInput();
				system("cls");
				break;
			}
		}
	}
	
	WaitForUserInput();
	return 0;
}

void WaitForUserInput()
{
	printf("\nPress a key to continue...");
	_getch();
}