#pragma once

#include"../../graphics/Renderable.h"
#include"../Component.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs {

	class TriangleComponent : public graphics::Renderable, public Component
	{
	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;
		void OnStateChange(ECSStates a_newState) override;

		// Empty constructor
		TriangleComponent();

		// Constructor with arguments
		TriangleComponent(const math::Vector4& a_color);

		// Override for the renderer 
		int GetVertexCount() override { return 3; }
	};

} }