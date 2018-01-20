#pragma once

#include"../math/Vector2.h"
#include"../math/Vector4.h"

namespace nano { namespace graphics { 

	// Base structure for vertex
	struct Vertex {
		math::Vector2 pos;
		math::Vector4 color;
	};

#define OFFSET_TO_COLOR offsetof(Vertex, color);

} } 