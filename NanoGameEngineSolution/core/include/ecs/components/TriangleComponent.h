#pragma once

#include"../RenderableComponent.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs {

	class TriangleComponent : public RenderableComponent
	{
	public:
		// Empty constructor
		TriangleComponent();

		// Constructor with arguments
		TriangleComponent(const math::Vector4& a_color);

		// Override for the renderer 
		int getVertexCount() const { return 3; }
	};

} }