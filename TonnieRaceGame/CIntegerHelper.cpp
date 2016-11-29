#include "CIntegerHelper.h"
#include <random>

int CIntegerHelper::GetRandomIntBetween(int min, int max) {
	if (max < 0) {
		max = 0;
	}
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max);
    
    return uni(rng);
}
