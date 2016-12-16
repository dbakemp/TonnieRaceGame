#include "CIntegerHelper.h"
#include <random>

int CIntegerHelper::GetRandomIntBetween(int min, int max)
{
	if (max < 0)
	{
		max = 0;
	}
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	return uni(rng);
}

int CIntegerHelper::BitStringToInt(std::string bitString)
{
	static const std::size_t MaxSize = CHAR_BIT * sizeof(unsigned long);
	if (bitString.size() > MaxSize) return 0; // handle error or just truncate?

	std::bitset<MaxSize> bits;
	std::istringstream is(bitString);
	is >> bits;
	return bits.to_ulong();
}
