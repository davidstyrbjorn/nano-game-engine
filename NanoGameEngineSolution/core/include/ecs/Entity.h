#pragma once

#include<string>
#include<vector>
#include<assert.h>
#include<type_traits>

#include"Component.h"
#include"components\RectangleComponent.h"
#include"components\SpriteComponent.h"
#include"components\TriangleComponent.h"
#include"components\SoundComponent.h"

namespace nano { namespace ecs {

	enum _ComponentTypes {
		TRIANGLE_COMPONENT,
		RECTANGLE_COMPONENT,
		SPRITE_COMPONENT,
		SOUND_COMPONENT,
		SCRIPT_COMPONENT,
		FOURWAY_MOVE_COMPONENT
	};

	class Transform;

	class Entity {
	private:
		std::string m_id;
		bool m_isDead = false, m_isActive = true;

		RenderableComponent *m_RenderableComponent = nullptr;
		SoundComponent* m_SoundComponent = nullptr;
		Transform *m_TranformComponent = nullptr;
		Component *m_ScriptComponent = nullptr;
		Component* m_FourwayMoveComponent = nullptr;

	public:
		// Getters for components
		Transform* Transform();
		RenderableComponent* Renderable();
		SoundComponent* SoundComponent();
		template<typename _T> _T* ScriptComponent() { return static_cast<_T*>(m_ScriptComponent); }
		template<typename _T> _T* FourwayMoveComponent() { return static_cast<_T*>(m_FourwayMoveComponent); }

	public:
		// Default constrcutor
		Entity();

		// Constructor (string argument)
		Entity(const std::string &a_id);

		// Destructor
		~Entity();

	public:
		//////////
		// Component Methods
		//////////

		//////////
		// \brief Adds component of a_type to entity
		//
		template<typename ScriptComponent_T, typename FourwayMoveComponent_T>
		Component* AddComponent(_ComponentTypes a_type)
		{
			static_assert(std::is_base_of<Component, ScriptComponent_T>::value && std::is_base_of<Component, FourwayMoveComponent_T>::value);

			switch (a_type) {
			case _ComponentTypes::RECTANGLE_COMPONENT:
				m_RenderableComponent = new RectangleComponent();
				m_RenderableComponent->SetEntityOwner(this);
				m_RenderableComponent->Init();

				return m_RenderableComponent;
				break;
			case _ComponentTypes::TRIANGLE_COMPONENT:
				m_RenderableComponent = new TriangleComponent();
				m_RenderableComponent->SetEntityOwner(this);
				m_RenderableComponent->Init();

				return m_RenderableComponent;
				break;
			case _ComponentTypes::SPRITE_COMPONENT:
				m_RenderableComponent = new SpriteComponent();
				m_RenderableComponent->SetEntityOwner(this);
				m_RenderableComponent->Init();

				return m_RenderableComponent;
				break;
			case _ComponentTypes::SOUND_COMPONENT:
				m_SoundComponent = new ecs::SoundComponent();
				m_SoundComponent->SetEntityOwner(this);
				m_SoundComponent->Init();

				return m_SoundComponent;
				break;
			case _ComponentTypes::SCRIPT_COMPONENT:
				m_ScriptComponent = new ScriptComponent_T();
				m_ScriptComponent->SetEntityOwner(this);
				m_ScriptComponent->Init();

				return m_ScriptComponent;
				break;
			case _ComponentTypes::FOURWAY_MOVE_COMPONENT:
				m_FourwayMoveComponent = new FourwayMoveComponent_T();
				m_FourwayMoveComponent->SetEntityOwner(this);
				m_FourwayMoveComponent->Init();

				return m_FourwayMoveComponent;
				break;
			}
		}

		//////////
		// \brief Removes component of a_type from entity
		// 
		void RemoveComponent(_ComponentTypes a_type);

		//////////
		// Behavioural Methods
		//////////
		void Start();
		void Update();
		void FixedUpdate();

		//////////
		// Member getters
		//////////
		std::string GetID();
		std::string GetIDReference();
		bool IsDead();
		bool IsActive();

		//////////
		// Member setters
		//////////		
		void SetID(const std::string &a_id);
		void Kill();
		void Toggle();
		void Enable();
		void Disable();
	};
} }