#include"../include/EventHandler.h"

namespace nano { namespace editor {

	EventHandler::EventHandler()
	{

	}

	EventHandler::~EventHandler()
	{

	}

	void EventHandler::AddEvent(const BaseEvent a_event)
	{
		if (m_polledEvents.size() >= g_maxEvents) {
			m_polledEvents.pop_front();
		}
		m_polledEvents.push_back(a_event);
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

} }