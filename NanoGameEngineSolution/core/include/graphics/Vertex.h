#pragma once

#include"../math/Vector2.h"
#include"../math/Vector4.h"

namespace nano { namespace graphics { 

	// Base structure for vertex
	struct Vertex {
		math::Vector2 pos;
		math::Vector4 color;
		math::Vector2 uv;
		unsigned int textureSlot;
	};

// Offsets can be set at compile time
#define OFFSET_TO_COLOR offsetof(Vertex, color)
#define OFFSET_TO_UV offsetof(Vertex, uv)
#define OFFSET_TO_TEXTURE_SLOT offsetof(Vertex, textureSlot)

} } 