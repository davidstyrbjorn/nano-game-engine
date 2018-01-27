#pragma once

namespace nano { namespace ecs { 

	enum ECSStates {
		DISABLED = 0x0,
		ACTIVE = 0x1,
		DESTROYED = 0x2
	};

	typedef enum ECSEditorStates {
		HIGHLIGHTED = 1,
		NOT_HIGHLIGHTED = 0,
	};

} } 