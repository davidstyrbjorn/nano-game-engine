#pragma once

#include"Component.h"

namespace nano { namespace ecs { 

	class TestComponent : public Component {
	public:
		float floatData = 3.14156941f;

		void Start()
		{

		}

		void Update()
		{
			std::cout << "Update test component" << std::endl;
		}
	};

	class AnotherTestComponent : public Component {
	public:
		int intData = 3;

		void Start()
		{
		
		}

		void Update()
		{
			std::cout << "Update another test component" << std::endl;
		}
	};

} } 