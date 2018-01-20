#pragma once

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs { 

	class Transform {
	public:
		math::Vector2 position;
		float angle;

	public:
		// Default Constructor
		Transform();
	};

} }  