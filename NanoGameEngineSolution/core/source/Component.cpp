#include"../include/ecs/Component.h"

#include"../include/ecs/Entity.h"

namespace nano { namespace ecs {

	Entity & Component::GetEntityOwner()
	{
		return *m_owner;
	}

	void Component::SetEntityOwner(const Entity * a_entity)
	{
		m_owner = (Entity*)a_entity;
	}

} }