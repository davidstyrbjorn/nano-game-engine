#pragma once

#include<string>

namespace nano { namespace editor {  

	enum EventTypes {
		CREATED_ENTITY,
		REMOVED_ENTITY
	};

	struct BaseEvent {
		EventTypes _type;
	};

	struct EntityEvent : BaseEvent {
		std::string _id; // ID of the entity this event is handling
	};

} }