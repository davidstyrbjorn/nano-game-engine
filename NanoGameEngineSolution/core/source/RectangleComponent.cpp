#include"../include/ecs/components/RectangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	RectangleComponent::RectangleComponent()
	{

	}

	RectangleComponent::RectangleComponent(const math::Vector4 & a_color)
	{
		m_Color = a_color;
	}
	
}
}