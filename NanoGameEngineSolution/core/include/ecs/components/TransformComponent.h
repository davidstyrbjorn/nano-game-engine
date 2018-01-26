#pragma once

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs { 

	class Transform {
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
	};

} }  