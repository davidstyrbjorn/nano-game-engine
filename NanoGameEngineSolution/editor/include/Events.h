#pragma once

#include<string>

namespace nano { namespace editor {  

	enum EventTypes {
		CREATED_ENTITY,
		REMOVED_ENTITY,
		CLICKED_ON_ENTITY,
		RENAME_ENTITY,
		MANIPULATED_COMPONENT,
		MANIPULATED_ENTITY,
		CONSOLE_MESSAGE
	};

	struct BaseEvent {
		EventTypes _type; // Type of event
		std::string _strID; // Used almost everytime
		std::string _strID2; // Optional
		std::string _strID3; // Optional 2

		BaseEvent(EventTypes a_type, std::string a_strID, std::string a_strID2 = "-1", std::string a_strID3 = "-1") 
		{
			_type = a_type;
			_strID = a_strID;
			_strID2 = a_strID2;
			_strID3 = a_strID3;
		}
	};

} }