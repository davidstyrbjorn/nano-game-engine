#pragma once

namespace nano { namespace experimental { namespace ecs { 

	enum _ComponentTypes {
		RECTANGLE = 0x0, // renderable
		TRIANGLE = 0x1, // renderable
		SPRITE = 0x2, // renderable
		SOUND = 0x3,
		SCRIPT = 0x4,
		FOURWAY_MOVE = 0x5
	};

#define NUM_OF_COMPONENTS 4

} } } 