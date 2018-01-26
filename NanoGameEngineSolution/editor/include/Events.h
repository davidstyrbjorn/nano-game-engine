#pragma once

#include<string>

namespace nano { namespace editor {  

	enum EventTypes {
		CREATED_ENTITY,
		REMOVED_ENTITY,
		CLICKED_ON_ENTITY
	};

	struct BaseEvent {
		EventTypes _type;
		std::string _strID;
		BaseEvent(EventTypes a_type, std::string a_strID) {
			_type = a_type;
			_strID = a_strID;
		}
	};

} }