#pragma once

#include<deque>
#include<vector>
#include"Events.h"
#include"EventObserver.h"

namespace nano { namespace editor {

	class EventHandler {
	public:
		// Default Constructor
		EventHandler();

		// Destructor
		~EventHandler();

	private:
		std::deque<BaseEvent> m_polledEvents; // Current list of polled events
		std::vector<EventObserver*> m_eventObservers; // List of objects that wants to listen to events (-ish)
		const int g_maxEvents = 40; // max number of events

	public:
		// Methods
		void AddEvent(BaseEvent a_event); // Adds a_event to m_polledEvents
		void FlushEvents(); // Clears clears events inside m_polledEvents
		BaseEvent GetLatestEvent(); // Returns the most recent added event
		std::deque<BaseEvent>& GetEventsList(); // Returns event list

		void AddEventObserver(EventObserver* a_observer); // Adds a_observer to the observers list
	};
	
} }