#include <chrono>
#include <cstdint>
#include <limits>
#include <random>

#include "MathUtils.h"

int32_t MathUtils::GenerateRandomInt(int32_t minValue, int32_t maxValue)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int32_t> distribution(Min<int32_t>(minValue, maxValue), Max<int32_t>(minValue, maxValue));

	return distribution(generator);
}

float MathUtils::GenerateRandomFloat(float minValue, float maxValue)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_real_distribution<float> distribution(Min<float>(minValue, maxValue), Max<float>(minValue, maxValue));

	return distribution(generator);
}