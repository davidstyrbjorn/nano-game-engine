#include"../include/CoreEntryPoint.h"

#include"../include/Core.h"

#include<iostream>

namespace nano {

	void CoreEntryPoint::CoreInit()
	{
		std::cout << GetWelcomeMessage() << std::endl;
	}

	CoreEntryPoint::~CoreEntryPoint()
	{
		std::cout << "Nano Core has been destructed" << std::endl;
	}

}