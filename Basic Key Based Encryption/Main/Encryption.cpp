#include "Encryption.h"

void Encryption::Encrypt(std::string data, int type)
{
	std::vector<int> text_encrypted;
	ReadKey();

	if (type == Plain_Text)
	{
		int j = 0;
		for (int i = 0; i <= data.length(); i++)
		{
			text_encrypted.push_back((static_cast<int>(data[i]) + ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) + (static_cast<int>(_key->key[j]) * MULTIPLIER));

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
	}
	else if (type == File)
	{
		std::vector<std::string> file_contains;
		std::vector<std::string> file_contains_encrypted;
		std::string dummy;
		std::string file_path_new;
		std::string extension;
		ifstream file_read;

		// Prepare the new file path
		int j = 0;
		for (int i = data.length(); data[i] != '.'; i--)
		{
			extension += data[i];
			j++;
		}
		// Reverse the extension string and add the dot, so the extension is complete
		dummy += ".";
		for (int i = extension.length(); i > 0; i--)
		{
			if(extension[i] != 0)	
				dummy += extension[i];
		}
		extension = dummy;
		dummy = "";
		// paste the file path untill the file extension
		for (int i = 0; i < data.length() - j; i++)
		{
			dummy += data[i];
		}
		file_path_new = dummy + "-encrypted" + extension;

		// Read the data of the file
		file_read.open(data);
		while (getline(file_read, dummy))
			file_contains.push_back(dummy);
		file_read.close();

		// Encrypt the contains of the file and save it to the output file
		output.open(file_path_new);
		for (int i = 0; i < file_contains.size(); i++)
		{
			j = 0;
			for (int k = 0; k <= file_contains[i].length(); k++)
			{
				output << ((static_cast<int>(file_contains[i][k]) + ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) + (static_cast<int>(_key->key[j]) * MULTIPLIER));

				if (j != 31)
					j++;
				else
					j = 0;
			}
			output << '\n';
		}
		output.close();
	}
	else
	{
		return;
	}
	
	//Debug
#if EE_DEBUG == 1
	printf("\n\n\nNormal text: %s", data.c_str());
	std::cout << "\nEncrypted text: ";
	for (auto n : text_encrypted)
	{
		printf("%d ", n);
	}
#endif
}

void Encryption::Decrypt(std::string data, int type)
{
	int character[3];
	std::vector<char> text_decrypted;
	ReadKey();

	if (type == Plain_Text)
	{
		output.open("output_file.txt");
		int j = 0;
		for (int i = 0; i < data.length(); i++)
		{
			if (i == data.length() - 1)
				break;

			character[0] = static_cast<int>(data[i]) - NUMBERS_AS_TEXT_ERROR;
			character[1] = static_cast<int>(data[i + 1]) - NUMBERS_AS_TEXT_ERROR;
			character[2] = static_cast<int>(data[i + 2]) - NUMBERS_AS_TEXT_ERROR;
			i += 2;

			int dummy = character[0] * 100 + character[1] * 10 + character[2];
			char dummy_char = (static_cast<char>(dummy - ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) - ((static_cast<int>(_key->key[j]) * MULTIPLIER)));
			output << dummy_char;

			if (j != 31)
				j++;
			else
				j = 0;
		}

		
		output.close();
	}
	else if (type == File)
	{
		std::vector<std::string> file_contains;
		std::string dummy;
		std::string file_path_new;
		std::string extension;
		ifstream file_read;

		// Prepare the new file path
		int j = 0;
		for (int i = data.length(); data[i] != '.'; i--)
		{
			extension += data[i];
			j++;
	}
		// Reverse the extension string and add the dot, so the extension is complete
		dummy += ".";
		for (int i = extension.length(); i > 0; i--)
		{
			if (extension[i] != 0)
				dummy += extension[i];
		}
		extension = dummy;
		dummy = "";
		// paste the file path untill the file extension
		for (int i = 0; i < data.length() - j; i++)
		{
			dummy += data[i];
		}
		file_path_new = dummy + "-decrypted" + extension;

		// Read the data of the file
		file_read.open(data);
		while (getline(file_read, dummy))
			file_contains.push_back(dummy);
		file_read.close();

		// Encrypt the contains of the file and save it to the output file
		output.open(file_path_new);
		for (int i = 0; i < file_contains.size(); i++)
		{
			j = 0;
			for (int k = 0; k < file_contains[i].length(); k++)
			{
				if (k == file_contains[i].length() - 1)
					break;

				character[0] = static_cast<int>(file_contains[i][k]) - NUMBERS_AS_TEXT_ERROR;
				character[1] = static_cast<int>(file_contains[i][k + 1]) - NUMBERS_AS_TEXT_ERROR;
				character[2] = static_cast<int>(file_contains[i][k + 2]) - NUMBERS_AS_TEXT_ERROR;
				k += 2;

				int dummy_int = character[0] * 100 + character[1] * 10 + character[2];
				char dummy_char = (static_cast<char>(dummy_int - ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) - ((static_cast<int>(_key->key[j]) * MULTIPLIER)));
				output << dummy_char;

				if (j != 31)
					j++;
				else
					j = 0;
			}
			output << '\n';
		}
		output.close();
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