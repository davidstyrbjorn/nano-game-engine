#pragma once

#include<string>

namespace nano { namespace editor { 

	class EventObserver {
	public:
		virtual void OnEntityCreation(std::string a_id) { }
		virtual void OnEntityDestroyed(std::string a_id) { }
		virtual void OnEntityClick(std::string a_id) { }
		virtual void OnEntityRename(std::string a_id) { }

		virtual void OnComponentManipulation(std::string a_id, std::string a_id2, std::string a_id3) { }
		virtual void OnEntityManipulation(std::string a_id, std::string a_id2) { }

		virtual void OnNewConsoleMessage(std::string a_id) { }
	};

} }