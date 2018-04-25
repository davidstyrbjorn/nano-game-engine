#pragma once

#include"../RenderableComponent.h"

namespace nano { namespace ecs { 

	//class RectangleComponent : public graphics::Renderable, public Component
	class RectangleComponent : public RenderableComponent
	{
	public:
		// Empty constructor
		RectangleComponent();

		// Constructor with arguments
		RectangleComponent(const math::Vector4& a_color);

		// Override for the renderer to indicate primitive type
		int getVertexCount() const { return 4; }
	};

} }