#ifndef CIntegerHelper_h
#define CIntegerHelper_h

#include <stdio.h>
#include <bitset>
#include <string>
#include <sstream>
#include <climits>

class CIntegerHelper
{
public:
	static int GetRandomIntBetween(int min, int max);
	static int BitStringToInt(std::string bits);
private:
};

#endif /* CIntegerHelper_hpp */
