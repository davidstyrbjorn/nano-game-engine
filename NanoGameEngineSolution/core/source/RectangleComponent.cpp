#include"../include/ecs/components/RectangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	void RectangleComponent::Start()
	{

	}

	void RectangleComponent::Init()
	{
		m_transform = m_owner->m_transform;
	}

	void RectangleComponent::OnStateChange(ECSStates a_newState)
	{
		if (a_newState == ECSStates::DESTROYED) {
			m_owner->SetRenderableComponent(nullptr);
		}
	}

	RectangleComponent::RectangleComponent()
	{
	}

	RectangleComponent::RectangleComponent(const math::Vector4 & a_color)
	{
		m_color = a_color;
	}
	
}
}