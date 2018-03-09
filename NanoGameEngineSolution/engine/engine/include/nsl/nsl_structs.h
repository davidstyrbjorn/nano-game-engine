#pragma once

#include<string>
#include<vector>
#include<functional>

namespace nano {
	namespace ecs {
		class Entity;
	}
}

namespace nano { namespace engine {  

	struct ScriptCommand {
		std::string commandString;
		std::string arg;
	};

	struct ScriptLogicExpression {
		std::string logicString;
		std::string args;
		ScriptCommand command;
	};
} }