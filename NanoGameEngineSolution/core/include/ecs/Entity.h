#pragma once

#include<string>
#include<vector>
#include"ECS.h"

namespace nano { namespace ecs {

	class RenderableComponent;
	class SoundComponent;

	enum _ComponentTypes {
		TRIANGLE_COMPONENT,
		RECTANGLE_COMPONENT,
		SPRITE_COMPONENT,
		SOUND_COMPONENT,
	};

	class Transform;
	class Component;

	class Entity {
	private:
		std::string m_id;
		ECSStates m_state = ECSStates::ACTIVE;

		RenderableComponent *m_RenderableComponent = nullptr;
		SoundComponent* m_SoundComponent = nullptr;
		Transform *m_TranformComponent = nullptr;

	public:
		// Getters for components
		Transform* Transform();
		RenderableComponent* Renderable();
		SoundComponent* SoundComponent();

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
		Component* AddComponent(_ComponentTypes a_type);

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
		int GetState();

		//////////
		// Member setters
		//////////		
		void SetID(const std::string &a_id);
		void SetState(const int a_state);
	};
} }