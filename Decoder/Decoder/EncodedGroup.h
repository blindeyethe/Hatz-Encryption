#pragma once

#include <string>
#include "BitsGroup.h";

struct EncodedGroup
{
	BitsGroup decodedGroup;
	char encodedBit;

	std::string DecodedGroup()
	{
		std::string group;
		for (int i = 0; i < 4; i++) 
		{
			group.push_back(decodedGroup.bit[i]);
		}

		return group;
	}
};