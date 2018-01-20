#include "../include/ecs/components/TriangleComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	void ecs::TriangleComponent::Start()
	{
		m_transform = m_owner->m_transform;
	}

}
}
