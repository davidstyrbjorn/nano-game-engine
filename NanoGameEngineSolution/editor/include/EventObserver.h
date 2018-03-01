#pragma once

#include<string>

namespace nano { namespace editor { 

	class EventObserver {
	public:
		virtual void OnComponentManipulation(std::string a_id, std::string a_id2, std::string a_id3) { }
		virtual void OnEntityManipulation(std::string a_id, std::string a_id2) { }
		virtual void OnNewConsoleMessage(std::string a_id) { }
	};

} }