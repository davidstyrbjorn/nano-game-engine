#include"../include/Random.h"

#include<time.h>

namespace nano {
	
	std::random_device Random::m_randomDevice;

	int Random::GetRandomInteger(const int a_min, const int a_max)
	{
		std::mt19937 gen(m_randomDevice());

		std::uniform_int_distribution<int> _distribution(a_min, a_max);
		int _returnValue = _distribution(gen);

		return _returnValue;
	}

	float Random::GetRandomFloatingPoint(float a_min, float a_max)
	{
		srand(time(NULL));

		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = a_max - a_min;
		float r = random * diff;
		return a_min + r;
	}

}