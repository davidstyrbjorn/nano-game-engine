#pragma once

#include<string>
#include<vector>

namespace nano {
	namespace ecs {
		class Entity;
	}
}

namespace nano { namespace engine {  

	struct ScriptCommand {
		ecs::Entity* entity;
		std::string commandString;

		std::string arg;
	};

	struct LogicScriptCommand {

	};

} }