#pragma once

#include"../Component.h"

namespace nano { namespace ecs {  

	class FourwayMoveComponent : public Component
	{
	private:
		float a_velocity;

	public:
		// Default constructor
		FourwayMoveComponent(float a_velocity);

		// Component base methods
		void Start() override;
		void Update() override;
	};

} }