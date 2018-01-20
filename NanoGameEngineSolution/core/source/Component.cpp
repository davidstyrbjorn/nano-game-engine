#include"../include/ecs/Component.h"

#include"../include/ecs/Entity.h"

namespace nano { namespace ecs {

	const Entity & Component::GetEntityOwner()
	{
		return *m_owner;
	}

	void Component::SetEntityOwner(const Entity * a_entity)
	{
		m_owner = (Entity*)a_entity;
	}

	int ecs::Component::GetState()
	{
		return m_state;
	}

	void ecs::Component::SetState(const int a_state)
	{
		m_state = static_cast<ECSStates>(a_state);
	}

} }