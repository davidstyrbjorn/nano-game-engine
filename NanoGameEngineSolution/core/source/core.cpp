#include "..\include\Core.h"

namespace nano {

	Core* Core::_instance = nullptr;

	Core * nano::Core::Instance()
	{
		if (_instance == nullptr) {
			_instance = new Core();
		}
		return _instance;
	}

}
