#pragma once

#include<string>

namespace nano { namespace editor { 

	class EventObserver {
	public:
		virtual void OnEntityCreation(std::string a_id) { }
		virtual void OnEntityDestroyed(std::string a_id) { }
		virtual void OnEntityClick(std::string a_id) { }
	};

} }