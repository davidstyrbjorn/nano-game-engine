#include "../include/ecs/components/TriangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	TriangleComponent::TriangleComponent()
	{

	}

	TriangleComponent::TriangleComponent(const math::Vector4 & a_color)
	{
		m_Color = a_color;
	}

}
}
 