#pragma once

#include"../RenderableComponent.h"

namespace nano { namespace ecs { 

	//class RectangleComponent : public graphics::Renderable, public Component
	class RectangleComponent : RenderableComponent
	{
	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;
		void OnStateChange(ECSStates a_newState) override;

		// Empty constructor
		RectangleComponent();

		// Constructor with arguments
		RectangleComponent(const math::Vector4& a_color);

		// Override for the renderer 
		int getVertexCount() const override { return 4; }

		// Override
		ECSTickStates GetTickState() const override { return ECSTickStates::NEVER; }
	};

} }