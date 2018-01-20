#include"../include/ecs/components/RectangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	void RectangleComponent::Start()
	{
		m_transform = m_owner->m_transform;
	}

	RectangleComponent::RectangleComponent()
	{
		m_size = math::Vector2(0, 0);
		m_color = math::Vector4(0, 0, 0, 0);
	}

	RectangleComponent::RectangleComponent(const math::Vector2 & a_size, const math::Vector4 & a_color)
	{
		m_size = a_size;
		m_color = a_color;
	}
	
}
}