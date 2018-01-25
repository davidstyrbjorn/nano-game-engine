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
	};

} }