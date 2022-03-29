#pragma once

struct BitsGroup
{
	int bit[4];
};

bool IsSameBitsGroups(BitsGroup& group1, BitsGroup& group2)
{
	for (int i = 0; i < 4; i++)
	{
		if (group1.bit[i] != group2.bit[i])
			return false;
	}
	return true;
}