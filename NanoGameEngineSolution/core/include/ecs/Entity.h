#pragma once

#include<string>
#include<vector>
#include"ECS.h"
#include"components\TransformComponent.h"
#include"../graphics/Renderable.h"

namespace nano { namespace ecs {

	class Component;

	class Entity {
	private:
		std::string m_id;
		ECSStates m_state = ECSStates::ACTIVE;

		std::vector<Component*> m_componentsBag;

	public:
		// Every entity has a transform component
		Transform *m_transform;

	public:
		// Default constrcutor
		Entity();

		// Constructor (string argument)
		Entity(const std::string &a_id);

		// Constructor (char* argument)
		Entity(const char* a_id);

		// Destructor
		~Entity();

	public:
		//////////
		// Component Methods
		//////////

		//////////
		// \brief Pushes back component into components bag/list
		//
		void AddComponent(Component* a_componentToAdd);

		//////////
		// \brief Returns the component of type ComponentType if it exists in the components bag/list
		//
		template<typename ComponentType>
		ComponentType* GetComponent() {
			static std::string _componentName = typeid(ComponentType).name(); // Unique for each version of this methods
			for (int i = 0; i < m_componentsBag.size(); i++) {
				if (_componentName == typeid(*m_componentsBag[i]).name()) {
					return dynamic_cast<ComponentType*>(m_componentsBag[i]);
				}
			}
		}

		//////////
		// Behavioural Methods
		//////////
		void Start();
		void Update();

		//////////
		// Member getters
		//////////

		//////////
		// \brief Returns a string copy of the entities ID handle
		//
		inline std::string GetID() { return m_id; }

		//////////
		// \brief Returns a integer representation of the entities state
		//
		int GetState();

		//////////
		// Member setters
		//////////
		
		//////////
		// \brief Sets entities ID handle
		//
		void SetID(const std::string &a_id);

		//////////
		// \brief Sets entities state
		//
		void SetState(const int a_state);
	};
	
} }