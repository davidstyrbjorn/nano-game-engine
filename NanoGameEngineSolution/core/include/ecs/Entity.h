#pragma once

#include<string>
#include<vector>
#include"ECS.h"
#include"../graphics/Renderable.h"

// Component includes
#include"components\RectangleComponent.h"
#include"components\TriangleComponent.h"
#include"components\SpriteComponent.h"
#include"components\SoundComponent.h"

namespace nano { namespace ecs {

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

		graphics::Renderable* m_Renderable = nullptr;
		Component *m_RenderableComponent = nullptr;
		SoundComponent* m_SoundComponent = nullptr;
		Transform *m_TranformComponent = nullptr;

	public:
		// Getters for components
		Transform* Transform();
		graphics::Renderable* Renderable();
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