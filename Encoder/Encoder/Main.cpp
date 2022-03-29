#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Byte.h"
#include "EncodedByte.h"
#include "EncodedGroup.h"

void EncodeByte(char& byte);
char EncodeBitsGroup(BitsGroup& decodedGroup);

void GenerateEncodedGroup();
char GenerateRandomChar();

std::vector<char> GetBytes(std::string& directory);

void CreateEncodedFile();
void CreateKeyFile();

std::vector<EncodedGroup> encodedGroups;
std::vector<EncodedByte> encodedBytes;

int main()
{
	std::string fileDirectory;
	std::vector<char> fileBytes;

	std::cout << "File Directory: ";
	std::cin >> fileDirectory;

	GenerateEncodedGroup();
	fileBytes = GetBytes(fileDirectory);

	for (char& byte : fileBytes)
		EncodeByte(byte);

	CreateEncodedFile();
	CreateKeyFile();

	return 0;
}

void EncodeByte(char& byte)
{
	BitsGroup group1 = { (byte & 0x01) != 0, (byte & 0x02) != 0,
						 (byte & 0x04 )!= 0, (byte & 0x08) != 0 };

	BitsGroup group2 = { (byte & 0x10) != 0, (byte & 0x20) != 0,
						 (byte & 0x40) != 0, (byte & 0x80) != 0 };

	EncodedByte encodedByte{ EncodeBitsGroup(group1),  EncodeBitsGroup(group2) };

	encodedBytes.push_back(encodedByte);
}

char EncodeBitsGroup(BitsGroup& decodedGroup)
{
	for (EncodedGroup& group : encodedGroups)
	{
		if (IsSameBitsGroups(group.decodedGroup, decodedGroup))
			return group.encodedBit;
	}
}

void GenerateEncodedGroup()
{
	int digit[2] = { 0,1 };

	for (int i = 0; i < (1 << 4); i++)
	{
		EncodedGroup group{};

		group.decodedGroup = { digit[(i >> 0) & 1], digit[(i >> 1) & 1] , 
							   digit[(i >> 2) & 1], digit[(i >> 3) & 1] };

		encodedGroups.push_back(group);
	}

	srand(time(NULL));
	for (EncodedGroup& group : encodedGroups)
		group.encodedBit = GenerateRandomChar();
}

char GenerateRandomChar()
{
	char character = 97 + rand() % 26;

	for (EncodedGroup group : encodedGroups)
	{
		if (group.ContainsEncodedBit(character))
			character = GenerateRandomChar();
	}

	return character;
}

std::vector<char> GetBytes(std::string& directory)
{
	std::ifstream file(directory, std::ios::binary);

	std::vector<char> buffer
	{
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};

	return buffer;
}

void CreateEncodedFile()
{
	std::ofstream file("ENCODED FILE.tbe");

	for (EncodedByte& byte : encodedBytes)
		file << byte.bit[0] << byte.bit[1] << ' ';

	file.close();
}

void CreateKeyFile()
{
	std::ofstream file("KEY.tbe");

	for (EncodedGroup& group : encodedGroups)
		file << group.encodedBit << ' ';

	file.close();
}