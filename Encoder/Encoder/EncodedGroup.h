#pragma once
#include "BitsGroup.h"

struct EncodedGroup
{
	BitsGroup decodedGroup;
	char encodedBit;

	bool ContainsEncodedBit(char& bit)
	{
		return encodedBit == bit;
	}
};
