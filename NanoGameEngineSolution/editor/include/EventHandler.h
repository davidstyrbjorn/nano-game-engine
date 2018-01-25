#pragma once

#include<deque>
#include"Events.h"

namespace nano { namespace editor {

	class EventHandler {
	public:
		// Default Constructor
		EventHandler();

		// Destructor
		~EventHandler();

	private:
		std::deque<BaseEvent> m_polledEvents; // Current list of polled events
		const int g_maxEvents = 40; // max number of events

	public:
		// Methods
		void AddEvent(const BaseEvent a_event); // Adds a_event to m_polledEvents
		void FlushEvents(); // Clears clears events inside m_polledEvents
		BaseEvent GetLatestEvent(); // Returns the most recent added event
		std::deque<BaseEvent>& GetEventsList(); // Returns event list
	};
	
} }