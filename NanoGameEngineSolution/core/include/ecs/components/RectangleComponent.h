#pragma once

#include"../../graphics/Renderable.h"
#include"../Component.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs { 

	class RectangleComponent : public graphics::Renderable, public Component
	{
	public:
		// Inits the neccesary data
		void Start() override;

		// Empty constructor
		RectangleComponent();

		// Constructor with arguments
		RectangleComponent(const math::Vector2& a_size, const math::Vector4& a_color);

		// Override for the renderer 
		int GetVertexCount() override { return 4; }
	};

} }