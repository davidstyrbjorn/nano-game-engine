#pragma once

#include<random>

namespace nano {
		
	// Class taken from SudoGameEngine
	class Random {
	private:
		static std::random_device m_randomDevice;

	public:
		static int GetRandomInteger(const int a_min, const int a_max);
		static float GetRandomFloatingPoint(float a_min, float a_max);
	};

}