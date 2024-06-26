#include "Encryption.h"

void Encryption::Encrypt(std::string data, int type, char* path)
{
	std::vector<int> text_encrypted;
	ReadKey(path);

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
#if EE_DEBUG == 1
		{
			file_contains.push_back(dummy);
			printf("\nDummy: %s", dummy.c_str());
		}
#else
			file_contains.push_back(dummy);
#endif
		file_read.close();

		// Encrypt the contains of the file and save it to the output file
		output.open(file_path_new);
		for (int i = 0; i < file_contains.size(); i++)
		{
			j = 0;
			for (int k = 0; k <= file_contains[i].length(); k++)
			{
				if (file_contains[i][k] != '\0')
				{
#if EE_DEBUG == 1
					int dummy_int = ((static_cast<int>(file_contains[i][k]) + (static_cast<int>(_key->key[j]) - _key->shift) / 2) + (static_cast<int>(_key->key[j]) * MULTIPLIER));
					printf("\n\n\tNEW INT\nDummy int: %d", dummy_int);
					printf("\nKey Value with shift and halfed: %d", (static_cast<int>(_key->key[j]) - _key->shift) / 2);
					printf("\nBase key value: %d", static_cast<int>(_key->key[j]));
					printf("\nFile contains character Value: %d", static_cast<int>(file_contains[i][k]));
					printf("\nKey shift Value: %d", _key->shift);
					printf("\nKey Value: %d", (int)_key->key[j]);
#endif
					output << ((static_cast<int>(file_contains[i][k]) + (static_cast<int>(_key->key[j]) - _key->shift) / 2) + (static_cast<int>(_key->key[j]) * MULTIPLIER));

					if (j != 31)
						j++;
					else
						j = 0;
				}
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

void Encryption::Decrypt(std::string data, int type, char* path)
{
	int character[3];
	std::vector<char> text_decrypted;
	ReadKey(path);

	if (type == Plain_Text)
	{
		output.open("output_file.txt");
		int j = 0;
		for (int i = 0; i < data.length(); i++)
		{
			if (i == data.length() - 1)
				break;

			character[0] = static_cast<int>(data[i])     - NUMBERS_AS_TEXT_ERROR;
			character[1] = static_cast<int>(data[i + 1]) - NUMBERS_AS_TEXT_ERROR;
			character[2] = static_cast<int>(data[i + 2]) - NUMBERS_AS_TEXT_ERROR;
			// DEBUG
#if EE_DEBUG == 1
			printf("\n\nCharacter 0: %d\nCharacter 1: %d\nCharacter 2: %d",
				static_cast<int>(data[i]) - NUMBERS_AS_TEXT_ERROR,
				static_cast<int>(data[i + 1]) - NUMBERS_AS_TEXT_ERROR,
				static_cast<int>(data[i + 2]) - NUMBERS_AS_TEXT_ERROR);
#endif
			i += 2;

			int dummy = character[0] * 100 + character[1] * 10 + character[2];
			char dummy_char = (static_cast<char>(dummy - ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) - ((static_cast<int>(_key->key[j]) * MULTIPLIER)));
			output << dummy_char;
#if EE_DEBUG == 1
			printf("\n\nDummy char: %c", dummy_char);
#endif

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
#if EE_DEBUG == 1
		{
			file_contains.push_back(dummy);
			printf("\nDummy: %s", dummy.c_str());
		}
#else
			file_contains.push_back(dummy);
#endif
			
		file_read.close();

		// Encrypt the contains of the file and save it to the output file
		output.open(file_path_new);
		for (int i = 0; i < file_contains.size(); i++)
		{
			j = 0;
			for (int k = 0; k < file_contains[i].length(); k++)
			{
				if (file_contains[i][k] != '\0')
				{
					if (k == file_contains[i].length() - 1)
						break;

					character[0] = static_cast<int>(file_contains[i][k]) - NUMBERS_AS_TEXT_ERROR;
					character[1] = static_cast<int>(file_contains[i][k + 1]) - NUMBERS_AS_TEXT_ERROR;
					character[2] = static_cast<int>(file_contains[i][k + 2]) - NUMBERS_AS_TEXT_ERROR;
#if EE_DEBUG == 1
					printf("\n\n\n\tNEW CHAR\\/\nCharacter 0: %d\nCharacter 1: %d\nCharacter 2: %d",
						static_cast<int>(data[i]) - NUMBERS_AS_TEXT_ERROR,
						static_cast<int>(data[i + 1]) - NUMBERS_AS_TEXT_ERROR,
						static_cast<int>(data[i + 2]) - NUMBERS_AS_TEXT_ERROR);
#endif
					k += 2;

					int dummy_int = character[0] * 100 + character[1] * 10 + character[2];

					char dummy_char = (static_cast<char>(dummy_int - ((static_cast<int>(_key->key[j]) - _key->shift) / 2)) - ((static_cast<int>(_key->key[j]) * MULTIPLIER)));
					output << dummy_char;
#if EE_DEBUG == 1
					printf("\n\nDummy int: %d\nDummy char: %c", dummy_int, dummy_char);
#endif

					if (j != 31)
						j++;
					else
						j = 0;
				}
			}
			output << '\n';
		}
		output.close();
	}
}