#pragma once

#include<string>

namespace nano { namespace ecs {
	
	enum EntityState {
		DISABLED = 0x0,
		ACTIVE = 0x1,
		DESTROYED = 0x2
	};

	class Entity {
	private:
		std::string m_id;
		EntityState m_state;

	public:
		// Default constrcutor
		Entity() : m_id("unnamed") { }

		// Constructor (string argument)
		Entity(const std::string &a_id) : m_id(a_id) { }

		// Constructor (char* argument)
		Entity(const char* a_id) : m_id(a_id) { }

		// Destructor
		~Entity();

	public:
		//////////
		// Member getters
		//////////

		//////////
		// \brief Returns a string copy of the entities ID handle
		//
		inline std::string GetID();

		//////////
		// \brief Returns a integer representation of the entities state
		//
		inline int GetState();


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