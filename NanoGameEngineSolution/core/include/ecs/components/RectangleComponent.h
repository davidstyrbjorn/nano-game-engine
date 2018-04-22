#pragma once

#include"../RenderableComponent.h"

namespace nano { namespace ecs { 

	//class RectangleComponent : public graphics::Renderable, public Component
	class RectangleComponent : public RenderableComponent
	{
	public:
		// Inits the neccesary data
		void OnStateChange(ECSStates a_newState);

		// Empty constructor
		RectangleComponent();

		// Constructor with arguments
		RectangleComponent(const math::Vector4& a_color);

		// Override for the renderer 
		int getVertexCount() const { return 4; }

		// Override
		ECSTickStates GetTickState() const { return ECSTickStates::NEVER; }
	};

} }