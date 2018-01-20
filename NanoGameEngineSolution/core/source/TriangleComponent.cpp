#include "../include/ecs/components/TriangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	void ecs::TriangleComponent::Start()
	{
		m_transform = m_owner->m_transform;
	}

	TriangleComponent::TriangleComponent()
	{
		m_size = math::Vector2(0, 0);
		m_color = math::Vector4(0, 0, 0, 0);
	}

	TriangleComponent::TriangleComponent(const math::Vector2 & a_size, const math::Vector4 & a_color)
	{
		m_size = a_size;
		m_color = a_color;
	}

}
}
