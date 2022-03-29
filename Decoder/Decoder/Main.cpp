#include <iostream>
#include <fstream>
#include <vector>

#include "EncodedGroup.h"
#include "EncodedByte.h"

void CreateDecodedFile();

void ReadEncodedFile(std::string& directory);
void ReadKeyFile(std::string& directory);

void GenerateEncodedGroup();

std::vector<EncodedGroup> encodedGroups;
std::vector<EncodedByte> encodedBytes;

int main()
{
	std::string keyDirectory;
	std::string fileDirectory;

	std::cout << "Key Directory: ";
	std::cin >> keyDirectory;

	std::cout << "File Directory: ";
	std::cin >> fileDirectory;

	GenerateEncodedGroup();

	ReadKeyFile(keyDirectory);
	ReadEncodedFile(fileDirectory);

	CreateDecodedFile();
}

void CreateDecodedFile()
{
	std::fstream file("test.txt", std::ios::out);

	for (EncodedByte& byte : encodedBytes)
	{
		std::string decodedByte;
		std::string cacheByte;

		for (EncodedGroup& group : encodedGroups)
		{
			if (!decodedByte.empty() && !cacheByte.empty())
				break;

			if (byte.bit[0] == group.encodedBit)
				decodedByte = group.DecodedGroup();

			if (byte.bit[1] == group.encodedBit)
				cacheByte = group.DecodedGroup();
		}

		decodedByte.append(cacheByte);

		//file << decodedByte << ' ';
		file.write((char*)&decodedByte, 1);
	}

	file.close();
}

void ReadEncodedFile(std::string& directory)
{
	int bitsCount = 0;
	char encodedbit;
	EncodedByte encodedByte{};
	
	std::ifstream file(directory);

	while (file >> encodedbit)
	{
		if (bitsCount > 1)
		{
			encodedBytes.push_back(encodedByte);
			bitsCount = 0;
		}

		encodedByte.bit[bitsCount++] = encodedbit;
	}

	encodedBytes.push_back(encodedByte);

	file.close();
}

void ReadKeyFile(std::string& directory)
{
	int bitsCount = 0;
	char encodedbit;

	std::ifstream file(directory);

	while (file >> encodedbit)
		encodedGroups[bitsCount++].encodedBit = encodedbit;

	file.close();
}

void GenerateEncodedGroup()
{
	char digit[2] = { '0','1' };

	for (int i = 0; i < (1 << 4); i++)
	{
		EncodedGroup group{};

		group.decodedGroup = { digit[(i >> 0) & 1], digit[(i >> 1) & 1] ,
							   digit[(i >> 2) & 1], digit[(i >> 3) & 1] };

		encodedGroups.push_back(group);
	}
}