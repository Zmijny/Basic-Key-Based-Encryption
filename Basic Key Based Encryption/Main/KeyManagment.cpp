#include "KeyManagment.h"
#include <conio.h>
#define EE_DEBUG 0

void KeyManagment::ReadKey(char* path)
{
	std::string path_string = path;
	std::string key_file_path = "";

	int j = 0;
	for (int i = path_string.length(); path_string[i] != '\\'; i--)
	{
		j++;
	}
	for (int i = 0; i < path_string.length() - j; i++)
	{
		key_file_path += path_string[i];
	}
	key_file_path += '\\';
	key_file_path += KEY_FILENAME;
	
	key_file_input.open(key_file_path, std::ios::binary);
	if (!key_file_input.is_open())
	{
		printf("\nFile Failed to open\n");
		return;
	}
	key_file_input.read(reinterpret_cast<char*>(_key), sizeof(KeyData));
	/*
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(key_file_input), {});
	char* buffer_cstring = reinterpret_cast<char*>(buffer.data());
	memcpy(reinterpret_cast<void*>(_key), buffer_cstring, sizeof(KeyData));
	*/
#if EE_DEBUG == 1
	for (auto n : _key->key)
	{
		printf("\nKey character: %c ", n);
	}
	printf("\nShift value: %d\n\n", _key->shift);
#endif
	key_file_input.close();
}

void KeyManagment::SaveKey(char* path)
{
	std::string path_string = path;
	std::string key_file_path = "";

	int j = 0;
	for (int i = path_string.length(); path_string[i] != '\\'; i--)
	{
		j++;
	}
	for (int i = 0; i < path_string.length() - j; i++)
	{
		key_file_path += path_string[i];
	}
	key_file_path += '\\';
	key_file_path += KEY_FILENAME;

	key_file_output.open(key_file_path, std::ios::binary);
	key_file_output.write((char*)_key, sizeof(KeyData));
	key_file_output.close();
}

void KeyManagment::GenerateKey()
{
	srand(time(NULL));
	_key->shift = 1 + rand() % 5;
	// 33 - 125
	int random_char;
	for (int i = 0; i <= 31; i++)
	{
		//srand(time(NULL));
		random_char = 33 + rand() % (125 - 33);
		_key->key[i] = static_cast<char>(random_char);
	}

}