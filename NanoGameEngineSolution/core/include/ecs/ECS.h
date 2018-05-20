#pragma once

namespace nano { namespace ecs { 

	enum ECSStates {
		DISABLED = 0x0,
		ACTIVE = 0x1,
		DESTROYED = 0x2
	};

	enum ECSTickStates {
		FRAME,
		FIXED,
		NEVER
	};

	enum ComponentTypes {
		RECTANGLE_COMPONENT,
		TRIANGLE_COMPONENT,
		SPRITE_COMPONENT,
		SOUND_COMPONENT,
		FOURWAY_MOVE_COMPONENT,
		SCRIPT_COMPONENT
	};

} } 