#pragma once

#include <random>

class Random
{
private:

	inline static std::mt19937 s_RandomGenerator;
	inline static std::uniform_int_distribution<std::mt19937::result_type> s_Dist;

public:
	static void Init()
	{
		s_RandomGenerator.seed(std::random_device()());
	}

	static float Float()
	{
		return (float)s_Dist(s_RandomGenerator) / (float)std::numeric_limits<uint32_t>::max();
	}
};