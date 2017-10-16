#include "core/inc/RandomGenerator.h"

unsigned long int RandomGenerator::randIndex = 0;
/*
RandomGenerator::RandomGenerator()
{
	//Generate new random seed for every instance to hide patterns
	randIndex = randIndex + time(NULL);
}
*/

unsigned long int RandomGenerator::operator()()
{
	randIndex = (randIndex * 500041 + time(NULL)) % 542081;
	return randIndex;
}

std::string RandomGenerator::name()
{
	return names[(*this)() % NAME_COUNT];
}