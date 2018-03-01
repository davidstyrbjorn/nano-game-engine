#include"../include/EventHandler.h"

namespace nano { namespace editor {

	EventHandler::EventHandler()
	{

	}

	EventHandler::~EventHandler()
	{

	}

	void EventHandler::AddEvent(BaseEvent a_event)
	{
		// Add the event
		if (m_polledEvents.size() >= g_maxEvents) {
			m_polledEvents.pop_front();
		}
		m_polledEvents.push_back(a_event);

		// Message the observers
		//if (a_event._type == EventTypes::CREATED_ENTITY) {
		//	for (EventObserver *_observer : m_eventObservers) {
		//		_observer->OnEntityCreation(a_event._strID);
		//	}
		//}
		if (a_event._type == EventTypes::MANIPULATED_ENTITY) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnEntityManipulation(a_event._strID, a_event._strID2);
			}
		}
		else if (a_event._type == EventTypes::REMOVED_ENTITY) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnEntityDestroyed(a_event._strID);
			}
		}
		else if (a_event._type == EventTypes::CLICKED_ON_ENTITY) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnEntityClick(a_event._strID);
			}
		}
		else if (a_event._type == EventTypes::RENAME_ENTITY) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnEntityRename(a_event._strID);
			}
		}
		else if (a_event._type == EventTypes::MANIPULATED_COMPONENT) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnComponentManipulation(a_event._strID, a_event._strID2, a_event._strID3);
			}
		}
		else if (a_event._type == EventTypes::CONSOLE_MESSAGE) {
			for (EventObserver *_observer : m_eventObservers) {
				_observer->OnNewConsoleMessage(a_event._strID);
			}
		}
	}

	void EventHandler::FlushEvents()
	{
		m_polledEvents.clear();
	}

	BaseEvent EventHandler::GetLatestEvent()
	{
		return m_polledEvents.back();
	}

	std::deque<BaseEvent>& EventHandler::GetEventsList()
	{
		return m_polledEvents;
	}

	void EventHandler::AddEventObserver(EventObserver* a_observer)
	{
		m_eventObservers.push_back(a_observer);
	}

} }