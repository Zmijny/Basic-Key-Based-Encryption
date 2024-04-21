#include "KeyManagment.h"
#define EE_DEBUG 0

void KeyManagment::ReadKey()
{
	key_file_input.open(KEY_FILENAME, std::ios::binary);
	key_file_input.read((char*)_key, sizeof(KeyData));
#if EE_DEBUG == 1
	for (auto n : _key->key)
	{
		printf("%c ", n);
	}
#endif
	key_file_input.close();
}

void KeyManagment::SaveKey()
{
	key_file_output.open(KEY_FILENAME, std::ios::binary);
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