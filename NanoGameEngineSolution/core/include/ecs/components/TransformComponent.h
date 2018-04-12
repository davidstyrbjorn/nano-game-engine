#pragma once

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"
#include"../Component.h"

namespace nano { namespace ecs { 

	class Transform : public Component  {
	public:
		// C++11 Auto declaration
		math::Vector2 position = math::Vector2(0, 0);
		math::Vector2 size = math::Vector2(0 , 0);
		float angle;

	public:
		// Default Constructor
		Transform();

		/////////////
		// Setters
		/////////////

		void SetSize(math::Vector2 a_size);

		// Other
		void move(math::Vector2 a_direction, float a_speed);

		// Override
		ECSTickStates GetTickState() const override { return ECSTickStates::NEVER; }
	};

} }  