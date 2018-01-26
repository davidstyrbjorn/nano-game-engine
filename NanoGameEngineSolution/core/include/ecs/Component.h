#pragma once

#include"ECS.h"
#include"Entity.h"

namespace nano { namespace ecs { 

	class Component {
	protected:
		ECSStates m_state = ECSStates::ACTIVE;
		Entity* m_owner;

	public:
		virtual ~Component() { }

		//////////
		// \brief Init called after the component has been added to entity
		//
		virtual void Init() { } 

		//////////
		// \brief Start called by entity owner
		//
		virtual void Start() { }

		//////////
		// \brief Update called by entity owner
		//
		virtual void Update() { } 

		//////////
		// \brief Returns this components owner
		//
		const Entity& GetEntityOwner();
		//////////
		// \brief Sets this components owner
		//
		void SetEntityOwner(const Entity* a_entity);

		//////////
		// \brief Returns a integer representation of the entities state
		//
		int GetState();
		//////////
		// \brief Sets entities state
		//
		void SetState(const int a_state);
	};

} } 